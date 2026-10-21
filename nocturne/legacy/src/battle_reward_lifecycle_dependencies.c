/* Complete37 existing zero-credit lifecycle dependency bodies; fixed native-PC statements.
 * Actual128 upper halves survive every scalar write; external calls remain
 * explicitly unimplemented native bank/frame routes. No runtime decoder,
 * result provider, source register-zero fill or per-call upper-word trace. */
#include "battle_reward_lifecycle_dependencies.h"

#include "ee_fpu.h"
#include "script_compare.h"
#include <stdlib.h>
#include <string.h>
uint32_t *nocturneEffectHostFpr(void);
uint64_t nocturneEffectHostLo(void);
uint64_t nocturneEffectHostHi(void);
void nocturneEffectHostSetHilo(uint64_t lo,uint64_t hi);
static uint8_t *at(uint32_t a){return nocturneResolveBattleRewardLifecycleNativeAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneBattleRewardLifecycleNativeCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){
 uint32_t q[4];if(!r)return;nocturneBattleRewardLifecycleNativeCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);
 nocturneBattleRewardLifecycleNativeCpuWrite(r,q);if(r==29u)nocturneBattleRewardLifecycleNativeSetStackPointer(q[0]);
}
static uint32_t ea(unsigned r,int32_t offset){return (uint32_t)cpu(r)+(uint32_t)offset;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}




void nocturneBattleActionFormulaSecondaryWrite(uint64_t lo,uint64_t hi);
static void sb(uint32_t a,uint8_t v){*at(a)=v;}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sq(unsigned reg,uint32_t a){uint32_t q[4];nocturneBattleRewardLifecycleNativeCpuRead(reg,q);memcpy(at(a&~15u),q,16);}





static void requestLq(unsigned d,uint32_t a){uint32_t q[4];memcpy(q,at(a&~15u),16);nocturneBattleRewardLifecycleNativeCpuWrite(d,q);}
static void requestPacked(unsigned kind,unsigned d,unsigned s,unsigned t){
 uint32_t a[4],c[4],q[4];nocturneBattleRewardLifecycleNativeCpuRead(s,a);nocturneBattleRewardLifecycleNativeCpuRead(t,c);
 if(kind==0){q[0]=c[0];q[1]=c[1];q[2]=a[0];q[3]=a[1];}
 else if(kind==1){q[0]=a[2];q[1]=a[3];q[2]=c[2];q[3]=c[3];}
 else if(kind==2){for(unsigned i=0;i<4;i++)q[i]=a[i]&c[i];}
 else if(kind==3){for(unsigned i=0;i<4;i++)q[i]=~(a[i]|c[i]);}
 else if(kind==5){for(unsigned i=0;i<4;i++)q[i]=a[i]^c[i];}
 else{uint8_t x[16],y[16],z[16];memcpy(x,a,16);memcpy(y,c,16);for(unsigned i=0;i<16;i++)z[i]=(uint8_t)(x[i]-y[i]);memcpy(q,z,16);}
 nocturneBattleRewardLifecycleNativeCpuWrite(d,q);
}

#include "ee_fpu_sqrt.h"
#include "ee_vu_rotation.h"









static void body_001009e8(void);
static void body_00100a48(void);
static void body_00100c48(void);
static void body_00100d70(void);
static void body_00100e08(void);
static void body_00100e80(void);
static void body_00101aa0(void);
static void body_00105048(void);
static void body_0010dcb8(void);
static void body_0010e548(void);
static void body_0010e588(void);
static void body_0010e610(void);
static void body_001275d0(void);
static void body_00296648(void);
static void body_002966a8(void);
static void body_00296738(void);
static void body_002968f8(void);
static void body_00296b08(void);
static void body_00297460(void);
static void body_002a8120(void);
static void body_002a8170(void);
static void body_002a8ba8(void);
static void body_002a9650(void);
static void body_002be5b8(void);
static void body_002befc0(void);
static void body_002bf208(void);
static void body_002bf328(void);
static void body_002bf3a8(void);
static void body_002bf8f0(void);
static void body_002bfce8(void);
static void body_002bfd60(void);
static void body_002c2070(void);
static void body_002c6030(void);
static void body_002c6098(void);
static void body_002c60a8(void);
static void body_002d4310(void);
static void body_002d5924(void);
static void body_001009e8(void){
uint64_t incoming=cpu(31);
/* 001009e8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001009ec: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001009f0: lw s0,-0x5920(gp) */ lw(16,ea(28,(int32_t)UINT32_C(0xffffa6e0)));
/* 001009f4: beq s0,zero,0x00100a34 */ {int taken=(cpu(16)==cpu(0));/* delay 001009f8 */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_00100a34;}}
/* 001009fc: lh v0,0x2c(s0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x0000002c))));
L_00100a00:;
/* 00100a00: blez v0,0x00100a10 */ {int taken=((int64_t)cpu(2)<=0);/* delay 00100a04 */ set(3,half(ea(16,(int32_t)UINT32_C(0x0000002c))));if(taken){goto L_00100a10;}}
/* 00100a08: addiu v0,v1,-0x1 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
/* 00100a0c: sh v0,0x2c(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000002c)),(uint16_t)cpu(2));
L_00100a10:;
/* 00100a10: move v1,s0 */ set(3,cpu(16));
/* 00100a14: lw s0,0x3c(s0) */ lw(16,ea(16,(int32_t)UINT32_C(0x0000003c)));
/* 00100a18: lh v0,0x2c(v1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x0000002c))));
/* 00100a1c: bne v0,zero,0x00100a2c */ {int taken=(cpu(2)!=cpu(0));/* delay 00100a20 */ set(4,cpu(3));if(taken){goto L_00100a2c;}}
/* 00100a24: jal 0x001009a0 */ set(31,UINT64_C(0x00100a2c));/* delay 00100a28 */ nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x001009a0),UINT32_C(0x00100a24));
L_00100a2c:;
/* 00100a2c: bnel s0,zero,0x00100a00 */ {int taken=(cpu(16)!=cpu(0));if(taken){/* delay 00100a30 */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x0000002c))));goto L_00100a00;}}
L_00100a34:;
/* 00100a34: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00100a38: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00100a3c: jr ra */ {uint64_t target=cpu(31);/* delay 00100a40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00100a48(void){
uint64_t incoming=cpu(31);
/* 00100a48: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00100a4c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00100a50: move s0,a0 */ set(16,cpu(4));
/* 00100a54: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00100a58: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00100a5c: lw a0,0x1c(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 00100a60: andi v1,a0,0x20 */ set(3,cpu(4)&UINT32_C(0x00000020));
/* 00100a64: bne v1,zero,0x00100c34 */ {int taken=(cpu(3)!=cpu(0));/* delay 00100a68 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00100c34;}}
/* 00100a6c: andi v0,a0,0x10 */ set(2,cpu(4)&UINT32_C(0x00000010));
/* 00100a70: beq v0,zero,0x00100b10 */ {int taken=(cpu(2)==cpu(0));/* delay 00100a74 */ sw(ea(28,(int32_t)UINT32_C(0xffffa704)),(uint32_t)cpu(16));if(taken){goto L_00100b10;}}
/* 00100a78: lui v0,0x2f */ set(2,sx(UINT32_C(0x002f0000)));
/* 00100a7c: move t0,zero */ set(8,cpu(0));
/* 00100a80: addiu t2,v0,0x5810 */ set(10,sx((uint32_t)cpu(2)+UINT32_C(0x00005810)));
/* 00100a84: move a2,zero */ set(6,cpu(0));
/* 00100a88: move a1,zero */ set(5,cpu(0));
/* 00100a8c: addiu t1,gp,-0x5867 */ set(9,sx((uint32_t)cpu(28)+UINT32_C(0xffffa799)));
L_00100a90:;
/* 00100a90: addu v0,a1,t2 */ set(2,sx((uint32_t)cpu(5)+(uint32_t)cpu(10)));
/* 00100a94: li a3,0xf */ set(7,sx(UINT32_C(0x0000000f)));
L_00100a98:;
/* 00100a98: addiu a3,a3,-0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));
/* 00100a9c: sb zero,0x0(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));
/* 00100aa0: sb zero,0x20(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000020)),(uint8_t)cpu(0));
/* 00100aa4: nop  */ 
/* 00100aa8: nop  */ 
/* 00100aac: bgez a3,0x00100a98 */ {int taken=((int64_t)cpu(7)>=0);/* delay 00100ab0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));if(taken){goto L_00100a98;}}
/* 00100ab4: sll v0,t0,0x2 */ set(2,sx((uint32_t)cpu(8)<<2));
/* 00100ab8: move a0,a2 */ set(4,cpu(6));
/* 00100abc: addiu v1,gp,-0x5868 */ set(3,sx((uint32_t)cpu(28)+UINT32_C(0xffffa798)));
/* 00100ac0: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00100ac4: addu v0,v0,t1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(9)));
/* 00100ac8: li a3,0x1 */ set(7,sx(UINT32_C(0x00000001)));
/* 00100acc: nop  */ 
L_00100ad0:;
/* 00100ad0: addiu a3,a3,-0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));
/* 00100ad4: sb zero,0x0(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));
/* 00100ad8: addu at,a0,gp */ set(1,sx((uint32_t)cpu(4)+(uint32_t)cpu(28)));
/* 00100adc: sb zero,-0x5860(at) */ sb(ea(1,(int32_t)UINT32_C(0xffffa7a0)),(uint8_t)cpu(0));
/* 00100ae0: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 00100ae4: sb zero,0x0(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));
/* 00100ae8: addiu v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000002)));
/* 00100aec: bgez a3,0x00100ad0 */ {int taken=((int64_t)cpu(7)>=0);/* delay 00100af0 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000002)));if(taken){goto L_00100ad0;}}
/* 00100af4: addiu t0,t0,0x1 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00000001)));
/* 00100af8: addiu a2,a2,0x2 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000002)));
/* 00100afc: slti v0,t0,0x2 */ set(2,(int64_t)cpu(8)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 00100b00: bne v0,zero,0x00100a90 */ {int taken=(cpu(2)!=cpu(0));/* delay 00100b04 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000010)));if(taken){goto L_00100a90;}}
/* 00100b08: b 0x00100bd0 */ /* delay 00100b0c */ lw(2,ea(16,(int32_t)UINT32_C(0x00000030)));goto L_00100bd0;
L_00100b10:;
/* 00100b10: lui v0,0x2f */ set(2,sx(UINT32_C(0x002f0000)));
/* 00100b14: lui v1,0x2f */ set(3,sx(UINT32_C(0x002f0000)));
/* 00100b18: addiu t4,v0,0x5810 */ set(12,sx((uint32_t)cpu(2)+UINT32_C(0x00005810)));
/* 00100b1c: addiu t3,v1,0x57d0 */ set(11,sx((uint32_t)cpu(3)+UINT32_C(0x000057d0)));
/* 00100b20: move t0,zero */ set(8,cpu(0));
/* 00100b24: move t2,zero */ set(10,cpu(0));
/* 00100b28: move t1,zero */ set(9,cpu(0));
/* 00100b2c: nop  */ 
L_00100b30:;
/* 00100b30: addu a1,t1,t4 */ set(5,sx((uint32_t)cpu(9)+(uint32_t)cpu(12)));
/* 00100b34: addu a0,t1,t3 */ set(4,sx((uint32_t)cpu(9)+(uint32_t)cpu(11)));
/* 00100b38: li a3,0xf */ set(7,sx(UINT32_C(0x0000000f)));
/* 00100b3c: nop  */ 
L_00100b40:;
/* 00100b40: lbu v1,0x0(a0) */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 00100b44: addiu a3,a3,-0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));
/* 00100b48: lbu v0,0x20(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000020))));
/* 00100b4c: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 00100b50: sb v1,0x0(a1) */ sb(ea(5,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(3));
/* 00100b54: sb v0,0x20(a1) */ sb(ea(5,(int32_t)UINT32_C(0x00000020)),(uint8_t)cpu(2));
/* 00100b58: bgez a3,0x00100b40 */ {int taken=((int64_t)cpu(7)>=0);/* delay 00100b5c */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));if(taken){goto L_00100b40;}}
/* 00100b60: sll v0,t0,0x2 */ set(2,sx((uint32_t)cpu(8)<<2));
/* 00100b64: move a2,t2 */ set(6,cpu(10));
/* 00100b68: addiu a1,v0,0x1 */ set(5,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 00100b6c: li a3,0x1 */ set(7,sx(UINT32_C(0x00000001)));
L_00100b70:;
/* 00100b70: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 00100b74: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 00100b78: lbu v0,-0x1709(v0) */ set(2,byte(ea(2,(int32_t)UINT32_C(0xffffe8f7))));
/* 00100b7c: addiu a3,a3,-0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));
/* 00100b80: addu v1,a1,gp */ set(3,sx((uint32_t)cpu(5)+(uint32_t)cpu(28)));
/* 00100b84: lbu v1,-0x5878(v1) */ set(3,byte(ea(3,(int32_t)UINT32_C(0xffffa788))));
/* 00100b88: addu a0,a2,gp */ set(4,sx((uint32_t)cpu(6)+(uint32_t)cpu(28)));
/* 00100b8c: lbu a0,-0x5870(a0) */ set(4,byte(ea(4,(int32_t)UINT32_C(0xffffa790))));
/* 00100b90: lui at,0x55 */ set(1,sx(UINT32_C(0x00550000)));
/* 00100b94: addu at,at,a1 */ set(1,sx((uint32_t)cpu(1)+(uint32_t)cpu(5)));
/* 00100b98: sb v0,-0x16f9(at) */ sb(ea(1,(int32_t)UINT32_C(0xffffe907)),(uint8_t)cpu(2));
/* 00100b9c: addu at,a1,gp */ set(1,sx((uint32_t)cpu(5)+(uint32_t)cpu(28)));
/* 00100ba0: sb v1,-0x5868(at) */ sb(ea(1,(int32_t)UINT32_C(0xffffa798)),(uint8_t)cpu(3));
/* 00100ba4: addiu a1,a1,0x2 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
/* 00100ba8: addu at,a2,gp */ set(1,sx((uint32_t)cpu(6)+(uint32_t)cpu(28)));
/* 00100bac: sb a0,-0x5860(at) */ sb(ea(1,(int32_t)UINT32_C(0xffffa7a0)),(uint8_t)cpu(4));
/* 00100bb0: bgez a3,0x00100b70 */ {int taken=((int64_t)cpu(7)>=0);/* delay 00100bb4 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));if(taken){goto L_00100b70;}}
/* 00100bb8: addiu t0,t0,0x1 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00000001)));
/* 00100bbc: addiu t2,t2,0x2 */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0x00000002)));
/* 00100bc0: slti v0,t0,0x2 */ set(2,(int64_t)cpu(8)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 00100bc4: bne v0,zero,0x00100b30 */ {int taken=(cpu(2)!=cpu(0));/* delay 00100bc8 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0x00000010)));if(taken){goto L_00100b30;}}
/* 00100bcc: lw v0,0x30(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000030)));
L_00100bd0:;
/* 00100bd0: beq v0,zero,0x00100c20 */ {int taken=(cpu(2)==cpu(0));/* delay 00100bd4 */ set(17,sx(UINT32_C(0xffffffff)));if(taken){goto L_00100c20;}}
/* 00100bd8: beql v0,s1,0x00100c24 */ {int taken=(cpu(2)==cpu(17));if(taken){/* delay 00100bdc */ lw(3,ea(16,(int32_t)UINT32_C(0x00000028)));goto L_00100c24;}}
/* 00100be0: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x00100be8));/* delay 00100be4 */ set(4,cpu(16));nocturneBattleRewardLifecycleNativeIndirect(target,UINT32_C(0x00100be0));}
/* 00100be8: bnel v0,zero,0x00100bf0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00100bec */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(2));goto L_00100bf0;}}
L_00100bf0:;
/* 00100bf0: bnel v0,s1,0x00100c24 */ {int taken=(cpu(2)!=cpu(17));if(taken){/* delay 00100bf4 */ lw(3,ea(16,(int32_t)UINT32_C(0x00000028)));goto L_00100c24;}}
/* 00100bf8: lw v0,0x1c(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 00100bfc: li v1,0x2 */ set(3,sx(UINT32_C(0x00000002)));
/* 00100c00: andi v0,v0,0xf */ set(2,cpu(2)&UINT32_C(0x0000000f));
/* 00100c04: bnel v0,v1,0x00100c24 */ {int taken=(cpu(2)!=cpu(3));if(taken){/* delay 00100c08 */ lw(3,ea(16,(int32_t)UINT32_C(0x00000028)));goto L_00100c24;}}
/* 00100c0c: jal 0x00100e08 */ set(31,UINT64_C(0x00100c14));/* delay 00100c10 */ set(4,cpu(16));body_00100e08();
/* 00100c14: sw zero,-0x58fc(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa704)),(uint32_t)cpu(0));
/* 00100c18: b 0x00100c34 */ /* delay 00100c1c */ set(2,cpu(0));goto L_00100c34;
L_00100c20:;
/* 00100c20: lw v1,0x28(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000028)));
L_00100c24:;
/* 00100c24: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00100c28: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 00100c2c: sw v1,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(3));
/* 00100c30: sw zero,-0x58fc(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa704)),(uint32_t)cpu(0));
L_00100c34:;
/* 00100c34: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00100c38: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00100c3c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00100c40: jr ra */ {uint64_t target=cpu(31);/* delay 00100c44 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00100c48(void){
uint64_t incoming=cpu(31);
/* 00100c48: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00100c4c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00100c50: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00100c54: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00100c58: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00100c5c: lw s0,-0x5908(gp) */ lw(16,ea(28,(int32_t)UINT32_C(0xffffa6f8)));
/* 00100c60: lw s2,-0x5914(gp) */ lw(18,ea(28,(int32_t)UINT32_C(0xffffa6ec)));
/* 00100c64: nop  */ 
L_00100c68:;
/* 00100c68: beq s0,zero,0x00100d18 */ {int taken=(cpu(16)==cpu(0));/* delay 00100c6c */ if(taken){goto L_00100d18;}}
/* 00100c70: beq s2,zero,0x00100ce0 */ {int taken=(cpu(18)==cpu(0));/* delay 00100c74 */ set(4,cpu(16));if(taken){goto L_00100ce0;}}
/* 00100c78: lw v1,0x20(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 00100c7c: lw v0,0x20(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000020)));
/* 00100c80: sltu v0,v0,v1 */ set(2,cpu(2)<cpu(3));
/* 00100c84: bne v0,zero,0x00100cb8 */ {int taken=(cpu(2)!=cpu(0));/* delay 00100c88 */ set(4,cpu(18));if(taken){goto L_00100cb8;}}
/* 00100c8c: move a0,s0 */ set(4,cpu(16));
/* 00100c90: jal 0x00100a48 */ set(31,UINT64_C(0x00100c98));/* delay 00100c94 */ lw(17,ea(16,(int32_t)UINT32_C(0x00000040)));body_00100a48();
/* 00100c98: beq v0,zero,0x00100ca8 */ {int taken=(cpu(2)==cpu(0));/* delay 00100c9c */ if(taken){goto L_00100ca8;}}
/* 00100ca0: b 0x00100c68 */ /* delay 00100ca4 */ lw(16,ea(16,(int32_t)UINT32_C(0x0000003c)));goto L_00100c68;
L_00100ca8:;
/* 00100ca8: beql s1,zero,0x00100c68 */ {int taken=(cpu(17)==cpu(0));if(taken){/* delay 00100cac */ lw(16,ea(28,(int32_t)UINT32_C(0xffffa6f8)));goto L_00100c68;}}
/* 00100cb0: b 0x00100c68 */ /* delay 00100cb4 */ lw(16,ea(17,(int32_t)UINT32_C(0x0000003c)));goto L_00100c68;
L_00100cb8:;
/* 00100cb8: jal 0x00100a48 */ set(31,UINT64_C(0x00100cc0));/* delay 00100cbc */ lw(17,ea(18,(int32_t)UINT32_C(0x00000040)));body_00100a48();
/* 00100cc0: beq v0,zero,0x00100cd0 */ {int taken=(cpu(2)==cpu(0));/* delay 00100cc4 */ if(taken){goto L_00100cd0;}}
/* 00100cc8: b 0x00100c68 */ /* delay 00100ccc */ lw(18,ea(18,(int32_t)UINT32_C(0x0000003c)));goto L_00100c68;
L_00100cd0:;
/* 00100cd0: beql s1,zero,0x00100c68 */ {int taken=(cpu(17)==cpu(0));if(taken){/* delay 00100cd4 */ lw(18,ea(28,(int32_t)UINT32_C(0xffffa6ec)));goto L_00100c68;}}
/* 00100cd8: b 0x00100c68 */ /* delay 00100cdc */ lw(18,ea(17,(int32_t)UINT32_C(0x0000003c)));goto L_00100c68;
L_00100ce0:;
/* 00100ce0: jal 0x00100a48 */ set(31,UINT64_C(0x00100ce8));/* delay 00100ce4 */ lw(17,ea(16,(int32_t)UINT32_C(0x00000040)));body_00100a48();
/* 00100ce8: beq v0,zero,0x00100cf8 */ {int taken=(cpu(2)==cpu(0));/* delay 00100cec */ if(taken){goto L_00100cf8;}}
/* 00100cf0: b 0x00100d04 */ /* delay 00100cf4 */ lw(16,ea(16,(int32_t)UINT32_C(0x0000003c)));goto L_00100d04;
L_00100cf8:;
/* 00100cf8: beql s1,zero,0x00100d04 */ {int taken=(cpu(17)==cpu(0));if(taken){/* delay 00100cfc */ lw(16,ea(28,(int32_t)UINT32_C(0xffffa6f8)));goto L_00100d04;}}
/* 00100d00: lw s0,0x3c(s1) */ lw(16,ea(17,(int32_t)UINT32_C(0x0000003c)));
L_00100d04:;
/* 00100d04: bne s0,zero,0x00100ce0 */ {int taken=(cpu(16)!=cpu(0));/* delay 00100d08 */ set(4,cpu(16));if(taken){goto L_00100ce0;}}
/* 00100d0c: b 0x00100d58 */ /* delay 00100d10 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00100d58;
L_00100d18:;
/* 00100d18: beq s2,zero,0x00100d58 */ {int taken=(cpu(18)==cpu(0));/* delay 00100d1c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00100d58;}}
/* 00100d20: move a0,s2 */ set(4,cpu(18));
/* 00100d24: nop  */ 
L_00100d28:;
/* 00100d28: jal 0x00100a48 */ set(31,UINT64_C(0x00100d30));/* delay 00100d2c */ lw(17,ea(18,(int32_t)UINT32_C(0x00000040)));body_00100a48();
/* 00100d30: beq v0,zero,0x00100d40 */ {int taken=(cpu(2)==cpu(0));/* delay 00100d34 */ if(taken){goto L_00100d40;}}
/* 00100d38: b 0x00100d4c */ /* delay 00100d3c */ lw(18,ea(18,(int32_t)UINT32_C(0x0000003c)));goto L_00100d4c;
L_00100d40:;
/* 00100d40: beql s1,zero,0x00100d4c */ {int taken=(cpu(17)==cpu(0));if(taken){/* delay 00100d44 */ lw(18,ea(28,(int32_t)UINT32_C(0xffffa6ec)));goto L_00100d4c;}}
/* 00100d48: lw s2,0x3c(s1) */ lw(18,ea(17,(int32_t)UINT32_C(0x0000003c)));
L_00100d4c:;
/* 00100d4c: bne s2,zero,0x00100d28 */ {int taken=(cpu(18)!=cpu(0));/* delay 00100d50 */ set(4,cpu(18));if(taken){goto L_00100d28;}}
/* 00100d54: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00100d58:;
/* 00100d58: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00100d5c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00100d60: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00100d64: jr ra */ {uint64_t target=cpu(31);/* delay 00100d68 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
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
/* 00100d98: jal 0x00101738 */ set(31,UINT64_C(0x00100da0));/* delay 00100d9c */ set(5,cpu(0));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x00101738),UINT32_C(0x00100d98));
/* 00100da0: move a0,s0 */ set(4,cpu(16));
/* 00100da4: bnel a0,zero,0x00100d98 */ {int taken=(cpu(4)!=cpu(0));if(taken){/* delay 00100da8 */ lw(16,ea(4,(int32_t)UINT32_C(0x0000004c)));goto L_00100d98;}}
L_00100dac:;
/* 00100dac: jal 0x001005e8 */ set(31,UINT64_C(0x00100db4));/* delay 00100db0 */ set(4,cpu(17));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x001005e8),UINT32_C(0x00100dac));
/* 00100db4: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 00100db8: addiu a0,a0,-0x22e8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffdd18)));
/* 00100dbc: jal 0x002d4748 */ set(31,UINT64_C(0x00100dc4));/* delay 00100dc0 */ set(5,cpu(17));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002d4748),UINT32_C(0x00100dbc));
/* 00100dc4: lw v0,0x34(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000034)));
/* 00100dc8: beql v0,zero,0x00100ddc */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00100dcc */ lw(2,ea(17,(int32_t)UINT32_C(0x0000001c)));goto L_00100ddc;}}
/* 00100dd0: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x00100dd8));/* delay 00100dd4 */ set(4,cpu(17));nocturneBattleRewardLifecycleNativeIndirect(target,UINT32_C(0x00100dd0));}
/* 00100dd8: lw v0,0x1c(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x0000001c)));
L_00100ddc:;
/* 00100ddc: li v1,-0x10 */ set(3,sx(UINT32_C(0xfffffff0)));
/* 00100de0: move a0,s1 */ set(4,cpu(17));
/* 00100de4: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 00100de8: jal 0x00101b80 */ set(31,UINT64_C(0x00100df0));/* delay 00100dec */ sw(ea(17,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x00101b80),UINT32_C(0x00100de8));
/* 00100df0: move a0,s1 */ set(4,cpu(17));
/* 00100df4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00100df8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00100dfc: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00100e00: j 0x002a8bd8 */ /* delay 00100e04 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a8bd8),UINT32_C(0x00100e00));return;
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
/* 00100e34: jal 0x001005e8 */ set(31,UINT64_C(0x00100e3c));/* delay 00100e38 */ nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x001005e8),UINT32_C(0x00100e34));
/* 00100e3c: li v0,-0x10 */ set(2,sx(UINT32_C(0xfffffff0)));
/* 00100e40: lw v1,0x1c(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 00100e44: move a0,s0 */ set(4,cpu(16));
/* 00100e48: and v1,v1,v0 */ set(3,cpu(3)&cpu(2));
/* 00100e4c: ori v1,v1,0x3 */ set(3,cpu(3)|UINT32_C(0x00000003));
/* 00100e50: jal 0x00100760 */ set(31,UINT64_C(0x00100e58));/* delay 00100e54 */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(3));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x00100760),UINT32_C(0x00100e50));
/* 00100e58: lh v0,0x2e(s0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x0000002e))));
/* 00100e5c: bne v0,zero,0x00100e6c */ {int taken=(cpu(2)!=cpu(0));/* delay 00100e60 */ set(4,cpu(16));if(taken){goto L_00100e6c;}}
/* 00100e64: jal 0x00100d70 */ set(31,UINT64_C(0x00100e6c));/* delay 00100e68 */ body_00100d70();
L_00100e6c:;
/* 00100e6c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00100e70:;
/* 00100e70: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00100e74: jr ra */ {uint64_t target=cpu(31);/* delay 00100e78 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00100e80(void){
uint64_t incoming=cpu(31);
/* 00100e80: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00100e84: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00100e88: lw s0,-0x5914(gp) */ lw(16,ea(28,(int32_t)UINT32_C(0xffffa6ec)));
/* 00100e8c: beq s0,zero,0x00100ecc */ {int taken=(cpu(16)==cpu(0));/* delay 00100e90 */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_00100ecc;}}
/* 00100e94: lh v0,0x2e(s0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x0000002e))));
L_00100e98:;
/* 00100e98: blez v0,0x00100ea8 */ {int taken=((int64_t)cpu(2)<=0);/* delay 00100e9c */ set(3,half(ea(16,(int32_t)UINT32_C(0x0000002e))));if(taken){goto L_00100ea8;}}
/* 00100ea0: addiu v0,v1,-0x1 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
/* 00100ea4: sh v0,0x2e(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000002e)),(uint16_t)cpu(2));
L_00100ea8:;
/* 00100ea8: move v1,s0 */ set(3,cpu(16));
/* 00100eac: lw s0,0x3c(s0) */ lw(16,ea(16,(int32_t)UINT32_C(0x0000003c)));
/* 00100eb0: lh v0,0x2e(v1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x0000002e))));
/* 00100eb4: bne v0,zero,0x00100ec4 */ {int taken=(cpu(2)!=cpu(0));/* delay 00100eb8 */ set(4,cpu(3));if(taken){goto L_00100ec4;}}
/* 00100ebc: jal 0x00100d70 */ set(31,UINT64_C(0x00100ec4));/* delay 00100ec0 */ body_00100d70();
L_00100ec4:;
/* 00100ec4: bnel s0,zero,0x00100e98 */ {int taken=(cpu(16)!=cpu(0));if(taken){/* delay 00100ec8 */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x0000002e))));goto L_00100e98;}}
L_00100ecc:;
/* 00100ecc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00100ed0: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00100ed4: jr ra */ {uint64_t target=cpu(31);/* delay 00100ed8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00101aa0(void){
uint64_t incoming=cpu(31);
/* 00101aa0: jr ra */ {uint64_t target=cpu(31);/* delay 00101aa4 */ lw(2,ea(4,(int32_t)UINT32_C(0x00000028)));checkReturn(target,incoming);return;}
}
static void body_00105048(void){
uint64_t incoming=cpu(31);
/* 00105048: addiu a1,gp,-0x57f5 */ set(5,sx((uint32_t)cpu(28)+UINT32_C(0xffffa80b)));
/* 0010504c: li v0,-0x80 */ set(2,sx(UINT32_C(0xffffff80)));
/* 00105050: bne a0,zero,0x00105078 */ {int taken=(cpu(4)!=cpu(0));/* delay 00105054 */ sb(ea(5,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));if(taken){goto L_00105078;}}
/* 00105058: lw v0,-0x5814(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa7ec)));
/* 0010505c: li v1,-0x4 */ set(3,sx(UINT32_C(0xfffffffc)));
/* 00105060: sb zero,0x0(a1) */ sb(ea(5,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));
/* 00105064: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 00105068: sh zero,-0x25b8(gp) */ sh(ea(28,(int32_t)UINT32_C(0xffffda48)),(uint16_t)cpu(0));
/* 0010506c: sw v0,-0x5814(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa7ec)),(uint32_t)cpu(2));
/* 00105070: jr ra */ {uint64_t target=cpu(31);/* delay 00105074 */ sh(ea(28,(int32_t)UINT32_C(0xffffda4a)),(uint16_t)cpu(0));checkReturn(target,incoming);return;}
L_00105078:;
/* 00105078: lw v0,-0x5814(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa7ec)));
/* 0010507c: li v1,-0x3 */ set(3,sx(UINT32_C(0xfffffffd)));
/* 00105080: sh a0,-0x25b8(gp) */ sh(ea(28,(int32_t)UINT32_C(0xffffda48)),(uint16_t)cpu(4));
/* 00105084: ori v0,v0,0x1 */ set(2,cpu(2)|UINT32_C(0x00000001));
/* 00105088: sh a0,-0x25b6(gp) */ sh(ea(28,(int32_t)UINT32_C(0xffffda4a)),(uint16_t)cpu(4));
/* 0010508c: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 00105090: jr ra */ {uint64_t target=cpu(31);/* delay 00105094 */ sw(ea(28,(int32_t)UINT32_C(0xffffa7ec)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
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
/* 0010dce4: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x0010dcec));/* delay 0010dce8 */ nocturneBattleRewardLifecycleNativeIndirect(target,UINT32_C(0x0010dce4));}
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
/* 0010dd1c: j 0x002a8bd8 */ /* delay 0010dd20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a8bd8),UINT32_C(0x0010dd1c));return;
L_0010dd28:;
/* 0010dd28: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010dd2c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010dd30: jr ra */ {uint64_t target=cpu(31);/* delay 0010dd34 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_0010e548(void){
uint64_t incoming=cpu(31);
/* 0010e548: lw v1,-0x57ac(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa854)));
/* 0010e54c: beq v1,zero,0x0010e55c */ {int taken=(cpu(3)==cpu(0));/* delay 0010e550 */ set(2,cpu(0));if(taken){goto L_0010e55c;}}
/* 0010e554: lw v1,0x18(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 0010e558: lw v0,0x8(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000008)));
L_0010e55c:;
/* 0010e55c: jr ra */ {uint64_t target=cpu(31);/* delay 0010e560 */ checkReturn(target,incoming);return;}
}
static void body_0010e588(void){
uint64_t incoming=cpu(31);
/* 0010e588: lw v1,-0x57ac(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa854)));
/* 0010e58c: beq v1,zero,0x0010e59c */ {int taken=(cpu(3)==cpu(0));/* delay 0010e590 */ set(2,cpu(0));if(taken){goto L_0010e59c;}}
/* 0010e594: lw v1,0x18(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 0010e598: lw v0,0xc(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x0000000c)));
L_0010e59c:;
/* 0010e59c: jr ra */ {uint64_t target=cpu(31);/* delay 0010e5a0 */ checkReturn(target,incoming);return;}
}
static void body_0010e610(void){
uint64_t incoming=cpu(31);
/* 0010e610: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0010e614: move a1,a0 */ set(5,cpu(4));
/* 0010e618: beq a1,zero,0x0010e680 */ {int taken=(cpu(5)==cpu(0));/* delay 0010e61c */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_0010e680;}}
/* 0010e620: lw v0,-0x57ac(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa854)));
/* 0010e624: beql v0,zero,0x0010e684 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0010e628 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0010e684;}}
/* 0010e62c: lw v1,0x18(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000018)));
/* 0010e630: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0010e634: bnel v0,a1,0x0010e648 */ {int taken=(cpu(2)!=cpu(5));if(taken){/* delay 0010e638 */ lw(2,ea(3,(int32_t)UINT32_C(0x00000004)));goto L_0010e648;}}
/* 0010e63c: lw v0,0x20(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000020)));
/* 0010e640: sw v0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0010e644: lw v0,0x4(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000004)));
L_0010e648:;
/* 0010e648: bnel v0,a1,0x0010e65c */ {int taken=(cpu(2)!=cpu(5));if(taken){/* delay 0010e64c */ lw(2,ea(3,(int32_t)UINT32_C(0x00000008)));goto L_0010e65c;}}
/* 0010e650: lw v0,0x24(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000024)));
/* 0010e654: sw v0,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 0010e658: lw v0,0x8(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000008)));
L_0010e65c:;
/* 0010e65c: beql v0,a1,0x0010e664 */ {int taken=(cpu(2)==cpu(5));if(taken){/* delay 0010e660 */ sw(ea(3,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));goto L_0010e664;}}
L_0010e664:;
/* 0010e664: lw v0,0xc(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x0000000c)));
/* 0010e668: beql v0,a1,0x0010e670 */ {int taken=(cpu(2)==cpu(5));if(taken){/* delay 0010e66c */ sw(ea(3,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));goto L_0010e670;}}
L_0010e670:;
/* 0010e670: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010e674: j 0x0010dcb8 */ /* delay 0010e678 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_0010dcb8();return;
L_0010e680:;
/* 0010e680: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
L_0010e684:;
/* 0010e684: jr ra */ {uint64_t target=cpu(31);/* delay 0010e688 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_001275d0(void){
uint64_t incoming=cpu(31);
/* 001275d0: lui v1,0x30 */ set(3,sx(UINT32_C(0x00300000)));
/* 001275d4: jr ra */ {uint64_t target=cpu(31);/* delay 001275d8 */ lw(2,ea(3,(int32_t)UINT32_C(0xffffc004)));checkReturn(target,incoming);return;}
}
static void body_00296648(void){
uint64_t incoming=cpu(31);
/* 00296648: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0029664c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296650: move s0,a0 */ set(16,cpu(4));
/* 00296654: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296658: li a0,0x6 */ set(4,sx(UINT32_C(0x00000006)));
/* 0029665c: lbu v1,0x1(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000001))));
/* 00296660: bne v1,a0,0x00296698 */ {int taken=(cpu(3)!=cpu(4));/* delay 00296664 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00296698;}}
/* 00296668: lw v0,0xc(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0029666c: beq v0,zero,0x0029667c */ {int taken=(cpu(2)==cpu(0));/* delay 00296670 */ set(4,cpu(2));if(taken){goto L_0029667c;}}
/* 00296674: jal 0x002bf688 */ set(31,UINT64_C(0x0029667c));/* delay 00296678 */ nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002bf688),UINT32_C(0x00296674));
L_0029667c:;
/* 0029667c: jal 0x002c60a8 */ set(31,UINT64_C(0x00296684));/* delay 00296680 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000030)));body_002c60a8();
/* 00296684: jal 0x002a8bd8 */ set(31,UINT64_C(0x0029668c));/* delay 00296688 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a8bd8),UINT32_C(0x00296684));
/* 0029668c: jal 0x002a8bd8 */ set(31,UINT64_C(0x00296694));/* delay 00296690 */ set(4,cpu(16));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a8bd8),UINT32_C(0x0029668c));
/* 00296694: move v0,zero */ set(2,cpu(0));
L_00296698:;
/* 00296698: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0029669c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002966a0: jr ra */ {uint64_t target=cpu(31);/* delay 002966a4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002966a8(void){
uint64_t incoming=cpu(31);
/* 002966a8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002966ac: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002966b0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002966b4: j 0x00296648 */ /* delay 002966b8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_00296648();return;
}
static void body_00296738(void){
uint64_t incoming=cpu(31);
/* 00296738: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0029673c: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 00296740: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00296744: move s2,a0 */ set(18,cpu(4));
/* 00296748: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0029674c: move s0,a3 */ set(16,cpu(7));
/* 00296750: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296754: move s1,t0 */ set(17,cpu(8));
/* 00296758: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0029675c: addiu s3,v0,0x5618 */ set(19,sx((uint32_t)cpu(2)+UINT32_C(0x00005618)));
/* 00296760: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00296764: move a0,a2 */ set(4,cpu(6));
/* 00296768: jal 0x002bfd60 */ set(31,UINT64_C(0x00296770));/* delay 0029676c */ sb(ea(18,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(5));body_002bfd60();
/* 00296770: sw s0,0x18(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(16));
/* 00296774: sw v0,0x8(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 00296778: sw s1,0x1c(s2) */ sw(ea(18,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(17));
/* 0029677c: jal 0x002dbee0 */ set(31,UINT64_C(0x00296784));/* delay 00296780 */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002dbee0),UINT32_C(0x0029677c));
/* 00296784: lw v0,0xc(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x0000000c)));
/* 00296788: bnel v0,zero,0x002967a0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0029678c */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(18));goto L_002967a0;}}
/* 00296790: sw s2,0x8(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(18));
/* 00296794: b 0x002967a4 */ /* delay 00296798 */ set(16,sx(UINT32_C(0x00000001)));goto L_002967a4;
L_002967a0:;
/* 002967a0: move s0,zero */ set(16,cpu(0));
L_002967a4:;
/* 002967a4: lw a0,0x0(s3) */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 002967a8: jal 0x002dbec0 */ set(31,UINT64_C(0x002967b0));/* delay 002967ac */ sw(ea(19,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(18));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002dbec0),UINT32_C(0x002967a8));
/* 002967b0: beq s0,zero,0x002967d0 */ {int taken=(cpu(16)==cpu(0));/* delay 002967b4 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002967d0;}}
/* 002967b8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002967bc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002967c0: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002967c4: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002967c8: j 0x00297460 */ /* delay 002967cc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(cpu(31),incoming);body_00297460();return;
L_002967d0:;
/* 002967d0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002967d4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002967d8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002967dc: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002967e0: jr ra */ {uint64_t target=cpu(31);/* delay 002967e4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002968f8(void){
uint64_t incoming=cpu(31);
/* 002968f8: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 002968fc: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00296900: move s6,a0 */ set(22,cpu(4));
/* 00296904: li a0,0x70 */ set(4,sx(UINT32_C(0x00000070)));
/* 00296908: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0029690c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296910: move s1,a2 */ set(17,cpu(6));
/* 00296914: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00296918: move s2,a1 */ set(18,cpu(5));
/* 0029691c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00296920: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00296924: move s4,a3 */ set(20,cpu(7));
/* 00296928: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0029692c: sd ra,0x38(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00296930: jal 0x002a8ba8 */ set(31,UINT64_C(0x00296938));/* delay 00296934 */ set(21,cpu(8));body_002a8ba8();
/* 00296938: move s3,v0 */ set(19,cpu(2));
/* 0029693c: move a1,s1 */ set(5,cpu(17));
/* 00296940: addiu s0,s3,0x30 */ set(16,sx((uint32_t)cpu(19)+UINT32_C(0x00000030)));
/* 00296944: jal 0x002c6030 */ set(31,UINT64_C(0x0029694c));/* delay 00296948 */ set(4,cpu(16));body_002c6030();
/* 0029694c: beq s2,zero,0x0029695c */ {int taken=(cpu(18)==cpu(0));/* delay 00296950 */ set(4,cpu(16));if(taken){goto L_0029695c;}}
/* 00296954: jal 0x002c6098 */ set(31,UINT64_C(0x0029695c));/* delay 00296958 */ body_002c6098();
L_0029695c:;
/* 0029695c: move a2,s6 */ set(6,cpu(22));
/* 00296960: move a3,s4 */ set(7,cpu(20));
/* 00296964: move t0,s5 */ set(8,cpu(21));
/* 00296968: move a0,s3 */ set(4,cpu(19));
/* 0029696c: jal 0x00296738 */ set(31,UINT64_C(0x00296974));/* delay 00296970 */ set(5,sx(UINT32_C(0x00000001)));body_00296738();
/* 00296974: move v0,s3 */ set(2,cpu(19));
/* 00296978: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0029697c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296980: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00296984: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00296988: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0029698c: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00296990: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00296994: ld ra,0x38(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00296998: jr ra */ {uint64_t target=cpu(31);/* delay 0029699c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_00296b08(void){
uint64_t incoming=cpu(31);
/* 00296b08: lhu v0,0x68(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x00000068))));
/* 00296b0c: beq v0,zero,0x00296b20 */ {int taken=(cpu(2)==cpu(0));/* delay 00296b10 */ set(3,cpu(0));if(taken){goto L_00296b20;}}
/* 00296b14: lbu v0,0x1(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000001))));
/* 00296b18: xori v0,v0,0x6 */ set(2,cpu(2)^UINT32_C(0x00000006));
/* 00296b1c: sltiu v1,v0,0x1 */ set(3,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
L_00296b20:;
/* 00296b20: jr ra */ {uint64_t target=cpu(31);/* delay 00296b24 */ set(2,cpu(3));checkReturn(target,incoming);return;}
}
static void body_00297460(void){
uint64_t incoming=cpu(31);
/* 00297460: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00297464: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 00297468: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0029746c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00297470: addiu s2,v0,0x5618 */ set(18,sx((uint32_t)cpu(2)+UINT32_C(0x00005618)));
/* 00297474: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00297478: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0029747c: jal 0x002dbee0 */ set(31,UINT64_C(0x00297484));/* delay 00297480 */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002dbee0),UINT32_C(0x0029747c));
/* 00297484: lw s0,0x8(s2) */ lw(16,ea(18,(int32_t)UINT32_C(0x00000008)));
/* 00297488: bnel s0,zero,0x002974b0 */ {int taken=(cpu(16)!=cpu(0));if(taken){/* delay 0029748c */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000000))));goto L_002974b0;}}
/* 00297490: lw a0,0x0(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 00297494: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00297498: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0029749c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002974a0: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002974a4: j 0x002dbec0 */ /* delay 002974a8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002dbec0),UINT32_C(0x002974a4));return;
L_002974b0:;
/* 002974b0: li s1,0x1 */ set(17,sx(UINT32_C(0x00000001)));
/* 002974b4: beq v1,s1,0x00297590 */ {int taken=(cpu(3)==cpu(17));/* delay 002974b8 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000002));if(taken){goto L_00297590;}}
/* 002974bc: beql v0,zero,0x002974d8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002974c0 */ set(2,sx(UINT32_C(0x00000002)));goto L_002974d8;}}
/* 002974c4: beql v1,zero,0x002974e8 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 002974c8 */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000001))));goto L_002974e8;}}
/* 002974cc: b 0x0029762c */ /* delay 002974d0 */ goto L_0029762c;
L_002974d8:;
/* 002974d8: beql v1,v0,0x002975f8 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 002974dc */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000001))));goto L_002975f8;}}
/* 002974e0: b 0x0029762c */ /* delay 002974e4 */ goto L_0029762c;
L_002974e8:;
/* 002974e8: beq v1,zero,0x00297500 */ {int taken=(cpu(3)==cpu(0));/* delay 002974ec */ set(2,sx(UINT32_C(0x00000007)));if(taken){goto L_00297500;}}
/* 002974f0: beq v1,v0,0x00297530 */ {int taken=(cpu(3)==cpu(2));/* delay 002974f4 */ if(taken){goto L_00297530;}}
/* 002974f8: b 0x0029762c */ /* delay 002974fc */ goto L_0029762c;
L_00297500:;
/* 00297500: sb s1,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(17));
/* 00297504: move s1,zero */ set(17,cpu(0));
/* 00297508: jal 0x002dbec0 */ set(31,UINT64_C(0x00297510));/* delay 0029750c */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002dbec0),UINT32_C(0x00297508));
/* 00297510: lui a1,0x29 */ set(5,sx(UINT32_C(0x00290000)));
/* 00297514: lw a0,0x8(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 00297518: addiu a1,a1,0x6fd8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00006fd8)));
/* 0029751c: jal 0x002bf3a8 */ set(31,UINT64_C(0x00297524));/* delay 00297520 */ set(6,cpu(16));body_002bf3a8();
/* 00297524: b 0x0029762c */ /* delay 00297528 */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));goto L_0029762c;
L_00297530:;
/* 00297530: jal 0x002a9288 */ set(31,UINT64_C(0x00297538));/* delay 00297534 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000014)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a9288),UINT32_C(0x00297530));
/* 00297538: bne v0,zero,0x00297568 */ {int taken=(cpu(2)!=cpu(0));/* delay 0029753c */ sw(ea(16,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));if(taken){goto L_00297568;}}
/* 00297540: lw v0,0xc(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 00297544: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 00297548: addiu a0,a0,0x68e8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000068e8)));
/* 0029754c: jal 0x002bd550 */ set(31,UINT64_C(0x00297554));/* delay 00297550 */ lw(5,ea(2,(int32_t)UINT32_C(0x00000010)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002bd550),UINT32_C(0x0029754c));
/* 00297554: lbu v1,0x2(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000002))));
/* 00297558: addiu v1,v1,0xff */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x000000ff)));
/* 0029755c: b 0x0029762c */ /* delay 00297560 */ sb(ea(16,(int32_t)UINT32_C(0x00000002)),(uint8_t)cpu(3));goto L_0029762c;
L_00297568:;
/* 00297568: jal 0x002a9688 */ set(31,UINT64_C(0x00297570));/* delay 0029756c */ set(4,cpu(2));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a9688),UINT32_C(0x00297568));
/* 00297570: li v1,0x3 */ set(3,sx(UINT32_C(0x00000003)));
/* 00297574: sw v0,0x24(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(2));
/* 00297578: move a0,s0 */ set(4,cpu(16));
/* 0029757c: sb v1,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(3));
/* 00297580: jal 0x00296f50 */ set(31,UINT64_C(0x00297588));/* delay 00297584 */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(2));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x00296f50),UINT32_C(0x00297580));
/* 00297588: b 0x0029762c */ /* delay 0029758c */ goto L_0029762c;
L_00297590:;
/* 00297590: lbu v1,0x1(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000001))));
/* 00297594: beq v1,zero,0x002975b0 */ {int taken=(cpu(3)==cpu(0));/* delay 00297598 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_002975b0;}}
/* 0029759c: beql v1,v0,0x002975e0 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 002975a0 */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));goto L_002975e0;}}
/* 002975a4: b 0x0029762c */ /* delay 002975a8 */ goto L_0029762c;
L_002975b0:;
/* 002975b0: sb s1,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(17));
/* 002975b4: move s1,zero */ set(17,cpu(0));
/* 002975b8: jal 0x002dbec0 */ set(31,UINT64_C(0x002975c0));/* delay 002975bc */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002dbec0),UINT32_C(0x002975b8));
/* 002975c0: lui a1,0x29 */ set(5,sx(UINT32_C(0x00290000)));
/* 002975c4: lw a0,0x8(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002975c8: addiu a1,a1,0x6d90 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00006d90)));
/* 002975cc: jal 0x002bf3a8 */ set(31,UINT64_C(0x002975d4));/* delay 002975d0 */ set(6,cpu(16));body_002bf3a8();
/* 002975d4: b 0x0029762c */ /* delay 002975d8 */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));goto L_0029762c;
L_002975e0:;
/* 002975e0: jal 0x002dbec0 */ set(31,UINT64_C(0x002975e8));/* delay 002975e4 */ set(17,cpu(0));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002dbec0),UINT32_C(0x002975e0));
/* 002975e8: jal 0x00296c88 */ set(31,UINT64_C(0x002975f0));/* delay 002975ec */ set(4,cpu(16));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x00296c88),UINT32_C(0x002975e8));
/* 002975f0: b 0x0029762c */ /* delay 002975f4 */ goto L_0029762c;
L_002975f8:;
/* 002975f8: bne v0,zero,0x0029762c */ {int taken=(cpu(2)!=cpu(0));/* delay 002975fc */ if(taken){goto L_0029762c;}}
/* 00297600: sb s1,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(17));
/* 00297604: move s1,zero */ set(17,cpu(0));
/* 00297608: jal 0x002dbec0 */ set(31,UINT64_C(0x00297610));/* delay 0029760c */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002dbec0),UINT32_C(0x00297608));
/* 00297610: lui a1,0x29 */ set(5,sx(UINT32_C(0x00290000)));
/* 00297614: lw a0,0x8(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 00297618: addiu a1,a1,0x72a0 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x000072a0)));
/* 0029761c: move a2,s0 */ set(6,cpu(16));
/* 00297620: jal 0x002bf410 */ set(31,UINT64_C(0x00297628));/* delay 00297624 */ set(7,sx(UINT32_C(0x00000180)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002bf410),UINT32_C(0x00297620));
/* 00297628: sw v0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
L_0029762c:;
/* 0029762c: beq s1,zero,0x00297640 */ {int taken=(cpu(17)==cpu(0));/* delay 00297630 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00297640;}}
/* 00297634: jal 0x002dbec0 */ set(31,UINT64_C(0x0029763c));/* delay 00297638 */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002dbec0),UINT32_C(0x00297634));
/* 0029763c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00297640:;
/* 00297640: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00297644: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00297648: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0029764c: jr ra */ {uint64_t target=cpu(31);/* delay 00297650 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002a8120(void){
uint64_t incoming=cpu(31);
/* 002a8120: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002a8124: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a8128: move s0,a1 */ set(16,cpu(5));
/* 002a812c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a8130: move s1,a0 */ set(17,cpu(4));
/* 002a8134: move a0,s0 */ set(4,cpu(16));
/* 002a8138: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a813c: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002a8140: jal 0x002a8170 */ set(31,UINT64_C(0x002a8148));/* delay 002a8144 */ set(18,cpu(6));body_002a8170();
/* 002a8148: move a0,s1 */ set(4,cpu(17));
/* 002a814c: move a2,s0 */ set(6,cpu(16));
/* 002a8150: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a8154: move a3,s2 */ set(7,cpu(18));
/* 002a8158: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a815c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a8160: move a1,v0 */ set(5,cpu(2));
/* 002a8164: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002a8168: j 0x002a80a8 */ /* delay 002a816c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a80a8),UINT32_C(0x002a8168));return;
}
static void body_002a8170(void){
uint64_t incoming=cpu(31);
/* 002a8170: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002a8174: slti v0,a0,0x401 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000401));
/* 002a8178: bne v0,zero,0x002a8198 */ {int taken=(cpu(2)!=cpu(0));/* delay 002a817c */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002a8198;}}
/* 002a8180: jal 0x002a9038 */ set(31,UINT64_C(0x002a8188));/* delay 002a8184 */ nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a9038),UINT32_C(0x002a8180));
/* 002a8188: jal 0x002a9688 */ set(31,UINT64_C(0x002a8190));/* delay 002a818c */ set(4,cpu(2));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a9688),UINT32_C(0x002a8188));
/* 002a8190: b 0x002a81a4 */ /* delay 002a8194 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002a81a4;
L_002a8198:;
/* 002a8198: jal 0x002a8af8 */ set(31,UINT64_C(0x002a81a0));/* delay 002a819c */ nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a8af8),UINT32_C(0x002a8198));
/* 002a81a0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002a81a4:;
/* 002a81a4: jr ra */ {uint64_t target=cpu(31);/* delay 002a81a8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002a8ba8(void){
uint64_t incoming=cpu(31);
/* 002a8ba8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002a8bac: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a8bb0: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a8bb4: jal 0x002a8af8 */ set(31,UINT64_C(0x002a8bbc));/* delay 002a8bb8 */ set(16,cpu(4));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a8af8),UINT32_C(0x002a8bb4));
/* 002a8bbc: addiu s0,s0,0xf */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x0000000f)));
/* 002a8bc0: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a8bc4: sra a1,s0,0x4 */ set(5,sx((uint32_t)((int32_t)cpu(16)>>4)));
/* 002a8bc8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a8bcc: move a0,v0 */ set(4,cpu(2));
/* 002a8bd0: j 0x002bfce8 */ /* delay 002a8bd4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002bfce8();return;
}
static void body_002a9650(void){
uint64_t incoming=cpu(31);
/* 002a9650: move v0,a0 */ set(2,cpu(4));
/* 002a9654: addiu a0,gp,-0x20f8 */ set(4,sx((uint32_t)cpu(28)+UINT32_C(0xffffdf08)));
/* 002a9658: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002a965c: move a1,v0 */ set(5,cpu(2));
/* 002a9660: beq v0,zero,0x002a9678 */ {int taken=(cpu(2)==cpu(0));/* delay 002a9664 */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002a9678;}}
/* 002a9668: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a966c: j 0x002ac7b0 */ /* delay 002a9670 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002ac7b0),UINT32_C(0x002a966c));return;
L_002a9678:;
/* 002a9678: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a967c: jr ra */ {uint64_t target=cpu(31);/* delay 002a9680 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002be5b8(void){
uint64_t incoming=cpu(31);
/* 002be5b8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002be5bc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002be5c0: move s0,a0 */ set(16,cpu(4));
/* 002be5c4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002be5c8: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002be5cc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002be5d0: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002be5d4: jal 0x002e4070 */ set(31,UINT64_C(0x002be5dc));/* delay 002be5d8 */ set(19,cpu(0));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002e4070),UINT32_C(0x002be5d4));
/* 002be5dc: lbu a0,0x14(s0) */ set(4,byte(ea(16,(int32_t)UINT32_C(0x00000014))));
/* 002be5e0: move s2,v0 */ set(18,cpu(2));
/* 002be5e4: sll v0,a0,0x1 */ set(2,sx((uint32_t)cpu(4)<<1));
/* 002be5e8: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002be5ec: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 002be5f0: lui s1,0x53 */ set(17,sx(UINT32_C(0x00530000)));
/* 002be5f4: addiu s1,s1,-0x6500 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffff9b00)));
/* 002be5f8: addu s1,s1,v0 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(2)));
/* 002be5fc: lw v1,0x0(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002be600: bgezl v1,0x002be614 */ {int taken=((int64_t)cpu(3)>=0);if(taken){/* delay 002be604 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd7dc)));goto L_002be614;}}
/* 002be608: jal 0x002bf8f0 */ set(31,UINT64_C(0x002be610));/* delay 002be60c */ body_002bf8f0();
/* 002be610: lw v0,-0x2824(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd7dc)));
L_002be614:;
/* 002be614: beq v0,zero,0x002be628 */ {int taken=(cpu(2)==cpu(0));/* delay 002be618 */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));if(taken){goto L_002be628;}}
/* 002be61c: b 0x002be62c */ /* delay 002be620 */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));goto L_002be62c;
L_002be628:;
/* 002be628: sw s0,-0x2828(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd7d8)),(uint32_t)cpu(16));
L_002be62c:;
/* 002be62c: lw v0,0xc(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 002be630: sw s0,-0x2824(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd7dc)),(uint32_t)cpu(16));
/* 002be634: beq v0,zero,0x002be648 */ {int taken=(cpu(2)==cpu(0));/* delay 002be638 */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));if(taken){goto L_002be648;}}
/* 002be63c: b 0x002be650 */ /* delay 002be640 */ sw(ea(2,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(16));goto L_002be650;
L_002be648:;
/* 002be648: sw s0,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(16));
/* 002be64c: li s3,0x1 */ set(19,sx(UINT32_C(0x00000001)));
L_002be650:;
/* 002be650: lhu v0,-0x2814(gp) */ set(2,half(ea(28,(int32_t)UINT32_C(0xffffd7ec))));
/* 002be654: sw s0,0xc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(16));
/* 002be658: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002be65c: beq s2,zero,0x002be66c */ {int taken=(cpu(18)==cpu(0));/* delay 002be660 */ sh(ea(28,(int32_t)UINT32_C(0xffffd7ec)),(uint16_t)cpu(2));if(taken){goto L_002be66c;}}
/* 002be664: jal 0x002e40b8 */ set(31,UINT64_C(0x002be66c));/* delay 002be668 */ nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002e40b8),UINT32_C(0x002be664));
L_002be66c:;
/* 002be66c: beq s3,zero,0x002be690 */ {int taken=(cpu(19)==cpu(0));/* delay 002be670 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002be690;}}
/* 002be674: lw a0,0x4(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 002be678: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002be67c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002be680: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002be684: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002be688: j 0x002dbec0 */ /* delay 002be68c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(cpu(31),incoming);nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002dbec0),UINT32_C(0x002be688));return;
L_002be690:;
/* 002be690: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002be694: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002be698: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002be69c: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002be6a0: jr ra */ {uint64_t target=cpu(31);/* delay 002be6a4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002befc0(void){
uint64_t incoming=cpu(31);
/* 002befc0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002befc4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002befc8: move s0,a1 */ set(16,cpu(5));
/* 002befcc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002befd0: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002befd4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002befd8: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002befdc: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002befe0: jal 0x002d5d0c */ set(31,UINT64_C(0x002befe8));/* delay 002befe4 */ set(20,cpu(4));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002d5d0c),UINT32_C(0x002befe0));
/* 002befe8: move s3,v0 */ set(19,cpu(2));
/* 002befec: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002beff0: beq s0,v0,0x002bf0c8 */ {int taken=(cpu(16)==cpu(2));/* delay 002beff4 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000002));if(taken){goto L_002bf0c8;}}
/* 002beff8: beq v0,zero,0x002bf010 */ {int taken=(cpu(2)==cpu(0));/* delay 002beffc */ set(2,sx(UINT32_C(0x00000002)));if(taken){goto L_002bf010;}}
/* 002bf000: beq s0,zero,0x002bf028 */ {int taken=(cpu(16)==cpu(0));/* delay 002bf004 */ set(2,cpu(0));if(taken){goto L_002bf028;}}
/* 002bf008: b 0x002bf1e8 */ /* delay 002bf00c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002bf1e8;
L_002bf010:;
/* 002bf010: beq s0,v0,0x002bf178 */ {int taken=(cpu(16)==cpu(2));/* delay 002bf014 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_002bf178;}}
/* 002bf018: beq s0,v0,0x002bf1c0 */ {int taken=(cpu(16)==cpu(2));/* delay 002bf01c */ set(2,cpu(0));if(taken){goto L_002bf1c0;}}
/* 002bf020: b 0x002bf1e8 */ /* delay 002bf024 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002bf1e8;
L_002bf028:;
/* 002bf028: jal 0x002a8af8 */ set(31,UINT64_C(0x002bf030));/* delay 002bf02c */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0x0000000a)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a8af8),UINT32_C(0x002bf028));
/* 002bf030: move s2,v0 */ set(18,cpu(2));
/* 002bf034: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002bf038: addiu a2,v0,0x1968 */ set(6,sx((uint32_t)cpu(2)+UINT32_C(0x00001968)));
/* 002bf03c: lwl v1,0x3(a2) */ {uint32_t a=ea(6,(int32_t)UINT32_C(0x00000003));unsigned o=a&3u;set(3,sx(((uint32_t)cpu(3)&(UINT32_C(0x00ffffff)>>(8u*o)))|(word(a&~3u)<<(24u-8u*o))));}
/* 002bf040: lwr v1,0x0(a2) */ {uint32_t a=ea(6,(int32_t)UINT32_C(0x00000000));unsigned o=a&3u;set(3,sx(((uint32_t)cpu(3)&(UINT32_C(0xffffff00)<<(24u-8u*o)))|(word(a&~3u)>>(8u*o))));}
/* 002bf044: lb a0,0x4(a2) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(6,(int32_t)UINT32_C(0x00000004))));
/* 002bf048: lb a1,0x5(a2) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(6,(int32_t)UINT32_C(0x00000005))));
/* 002bf04c: swl v1,0x3(s2) */ {uint32_t a=ea(18,(int32_t)UINT32_C(0x00000003));unsigned o=a&3u;sw(a&~3u,(word(a&~3u)&(UINT32_C(0xffffff00)<<(8u*o)))|((uint32_t)cpu(3)>>(24u-8u*o)));}
/* 002bf050: swr v1,0x0(s2) */ {uint32_t a=ea(18,(int32_t)UINT32_C(0x00000000));unsigned o=a&3u;sw(a&~3u,(word(a&~3u)&(UINT32_C(0x00ffffff)>>(24u-8u*o)))|((uint32_t)cpu(3)<<(8u*o)));}
/* 002bf054: sb a0,0x4(s2) */ sb(ea(18,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 002bf058: sb a1,0x5(s2) */ sb(ea(18,(int32_t)UINT32_C(0x00000005)),(uint8_t)cpu(5));
/* 002bf05c: lb v1,0x6(a2) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(6,(int32_t)UINT32_C(0x00000006))));
/* 002bf060: sb v1,0x6(s2) */ sb(ea(18,(int32_t)UINT32_C(0x00000006)),(uint8_t)cpu(3));
/* 002bf064: lb a0,0x0(s4) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(20,(int32_t)UINT32_C(0x00000000))));
/* 002bf068: beq a0,zero,0x002bf0ac */ {int taken=(cpu(4)==cpu(0));/* delay 002bf06c */ set(6,cpu(0));if(taken){goto L_002bf0ac;}}
/* 002bf070: li a3,0x2f */ set(7,sx(UINT32_C(0x0000002f)));
/* 002bf074: addiu a1,s2,0x7 */ set(5,sx((uint32_t)cpu(18)+UINT32_C(0x00000007)));
L_002bf078:;
/* 002bf078: bne a0,a3,0x002bf088 */ {int taken=(cpu(4)!=cpu(7));/* delay 002bf07c */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0xffffff9f)));if(taken){goto L_002bf088;}}
/* 002bf080: b 0x002bf094 */ /* delay 002bf084 */ set(4,sx(UINT32_C(0x0000005c)));goto L_002bf094;
L_002bf088:;
/* 002bf088: addiu v1,a0,-0x20 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0xffffffe0)));
/* 002bf08c: sltiu v0,v0,0x1a */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000001a));
/* 002bf090: movn a0,v1,v0 */ if(cpu(2)!=0){set(4,cpu(3));}
L_002bf094:;
/* 002bf094: sb a0,0x0(a1) */ sb(ea(5,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(4));
/* 002bf098: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 002bf09c: addu v0,s4,a2 */ set(2,sx((uint32_t)cpu(20)+(uint32_t)cpu(6)));
/* 002bf0a0: lb a0,0x0(v0) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 002bf0a4: bne a0,zero,0x002bf078 */ {int taken=(cpu(4)!=cpu(0));/* delay 002bf0a8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));if(taken){goto L_002bf078;}}
L_002bf0ac:;
/* 002bf0ac: addu v0,s2,a2 */ set(2,sx((uint32_t)cpu(18)+(uint32_t)cpu(6)));
/* 002bf0b0: li v1,0x3b */ set(3,sx(UINT32_C(0x0000003b)));
/* 002bf0b4: li a0,0x31 */ set(4,sx(UINT32_C(0x00000031)));
/* 002bf0b8: sb v1,0x7(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000007)),(uint8_t)cpu(3));
/* 002bf0bc: sb a0,0x8(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000008)),(uint8_t)cpu(4));
/* 002bf0c0: b 0x002bf1e0 */ /* delay 002bf0c4 */ sb(ea(2,(int32_t)UINT32_C(0x00000009)),(uint8_t)cpu(0));goto L_002bf1e0;
L_002bf0c8:;
/* 002bf0c8: lb v1,0x0(s4) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(20,(int32_t)UINT32_C(0x00000000))));
/* 002bf0cc: li v0,0x2f */ set(2,sx(UINT32_C(0x0000002f)));
/* 002bf0d0: beq v1,v0,0x002bf128 */ {int taken=(cpu(3)==cpu(2));/* delay 002bf0d4 */ if(taken){goto L_002bf128;}}
/* 002bf0d8: jal 0x002a8af8 */ set(31,UINT64_C(0x002bf0e0));/* delay 002bf0dc */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0x00000007)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a8af8),UINT32_C(0x002bf0d8));
/* 002bf0e0: move s2,v0 */ set(18,cpu(2));
/* 002bf0e4: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002bf0e8: addiu a2,v0,0x1970 */ set(6,sx((uint32_t)cpu(2)+UINT32_C(0x00001970)));
/* 002bf0ec: lwl v1,0x3(a2) */ {uint32_t a=ea(6,(int32_t)UINT32_C(0x00000003));unsigned o=a&3u;set(3,sx(((uint32_t)cpu(3)&(UINT32_C(0x00ffffff)>>(8u*o)))|(word(a&~3u)<<(24u-8u*o))));}
/* 002bf0f0: lwr v1,0x0(a2) */ {uint32_t a=ea(6,(int32_t)UINT32_C(0x00000000));unsigned o=a&3u;set(3,sx(((uint32_t)cpu(3)&(UINT32_C(0xffffff00)<<(24u-8u*o)))|(word(a&~3u)>>(8u*o))));}
/* 002bf0f4: lb a0,0x4(a2) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(6,(int32_t)UINT32_C(0x00000004))));
/* 002bf0f8: lb a1,0x5(a2) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(6,(int32_t)UINT32_C(0x00000005))));
/* 002bf0fc: swl v1,0x3(s2) */ {uint32_t a=ea(18,(int32_t)UINT32_C(0x00000003));unsigned o=a&3u;sw(a&~3u,(word(a&~3u)&(UINT32_C(0xffffff00)<<(8u*o)))|((uint32_t)cpu(3)>>(24u-8u*o)));}
/* 002bf100: swr v1,0x0(s2) */ {uint32_t a=ea(18,(int32_t)UINT32_C(0x00000000));unsigned o=a&3u;sw(a&~3u,(word(a&~3u)&(UINT32_C(0x00ffffff)>>(24u-8u*o)))|((uint32_t)cpu(3)<<(8u*o)));}
/* 002bf104: sb a0,0x4(s2) */ sb(ea(18,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 002bf108: sb a1,0x5(s2) */ sb(ea(18,(int32_t)UINT32_C(0x00000005)),(uint8_t)cpu(5));
/* 002bf10c: move a1,s4 */ set(5,cpu(20));
/* 002bf110: addiu a0,s2,0x6 */ set(4,sx((uint32_t)cpu(18)+UINT32_C(0x00000006)));
/* 002bf114: jal 0x002d43a4 */ set(31,UINT64_C(0x002bf11c));/* delay 002bf118 */ set(6,cpu(19));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002d43a4),UINT32_C(0x002bf114));
/* 002bf11c: addu v1,s2,s3 */ set(3,sx((uint32_t)cpu(18)+(uint32_t)cpu(19)));
/* 002bf120: b 0x002bf1e0 */ /* delay 002bf124 */ sb(ea(3,(int32_t)UINT32_C(0x00000006)),(uint8_t)cpu(0));goto L_002bf1e0;
L_002bf128:;
/* 002bf128: jal 0x002be588 */ set(31,UINT64_C(0x002bf130));/* delay 002bf12c */ nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002be588),UINT32_C(0x002bf128));
/* 002bf130: move s1,v0 */ set(17,cpu(2));
/* 002bf134: jal 0x002d5d0c */ set(31,UINT64_C(0x002bf13c));/* delay 002bf138 */ set(4,cpu(17));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002d5d0c),UINT32_C(0x002bf134));
/* 002bf13c: move s0,v0 */ set(16,cpu(2));
/* 002bf140: jal 0x002a8af8 */ set(31,UINT64_C(0x002bf148));/* delay 002bf144 */ set(4,sx((uint32_t)cpu(19)+(uint32_t)cpu(16)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a8af8),UINT32_C(0x002bf140));
/* 002bf148: move a1,s1 */ set(5,cpu(17));
/* 002bf14c: move s2,v0 */ set(18,cpu(2));
/* 002bf150: move a2,s0 */ set(6,cpu(16));
/* 002bf154: jal 0x002d43a4 */ set(31,UINT64_C(0x002bf15c));/* delay 002bf158 */ set(4,cpu(18));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002d43a4),UINT32_C(0x002bf154));
/* 002bf15c: addu a0,s2,s0 */ set(4,sx((uint32_t)cpu(18)+(uint32_t)cpu(16)));
/* 002bf160: addiu a1,s4,0x1 */ set(5,sx((uint32_t)cpu(20)+UINT32_C(0x00000001)));
/* 002bf164: jal 0x002d43a4 */ set(31,UINT64_C(0x002bf16c));/* delay 002bf168 */ set(6,cpu(19));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002d43a4),UINT32_C(0x002bf164));
/* 002bf16c: b 0x002bf1e4 */ /* delay 002bf170 */ set(2,cpu(18));goto L_002bf1e4;
L_002bf178:;
/* 002bf178: jal 0x002a8af8 */ set(31,UINT64_C(0x002bf180));/* delay 002bf17c */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0x00000006)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a8af8),UINT32_C(0x002bf178));
/* 002bf180: move s2,v0 */ set(18,cpu(2));
/* 002bf184: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002bf188: addiu a2,v0,0x1978 */ set(6,sx((uint32_t)cpu(2)+UINT32_C(0x00001978)));
/* 002bf18c: lwl v1,0x3(a2) */ {uint32_t a=ea(6,(int32_t)UINT32_C(0x00000003));unsigned o=a&3u;set(3,sx(((uint32_t)cpu(3)&(UINT32_C(0x00ffffff)>>(8u*o)))|(word(a&~3u)<<(24u-8u*o))));}
/* 002bf190: lwr v1,0x0(a2) */ {uint32_t a=ea(6,(int32_t)UINT32_C(0x00000000));unsigned o=a&3u;set(3,sx(((uint32_t)cpu(3)&(UINT32_C(0xffffff00)<<(24u-8u*o)))|(word(a&~3u)>>(8u*o))));}
/* 002bf194: lb a0,0x4(a2) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(6,(int32_t)UINT32_C(0x00000004))));
/* 002bf198: swl v1,0x3(s2) */ {uint32_t a=ea(18,(int32_t)UINT32_C(0x00000003));unsigned o=a&3u;sw(a&~3u,(word(a&~3u)&(UINT32_C(0xffffff00)<<(8u*o)))|((uint32_t)cpu(3)>>(24u-8u*o)));}
/* 002bf19c: swr v1,0x0(s2) */ {uint32_t a=ea(18,(int32_t)UINT32_C(0x00000000));unsigned o=a&3u;sw(a&~3u,(word(a&~3u)&(UINT32_C(0x00ffffff)>>(24u-8u*o)))|((uint32_t)cpu(3)<<(8u*o)));}
/* 002bf1a0: sb a0,0x4(s2) */ sb(ea(18,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 002bf1a4: move a1,s4 */ set(5,cpu(20));
/* 002bf1a8: addiu a0,s2,0x5 */ set(4,sx((uint32_t)cpu(18)+UINT32_C(0x00000005)));
/* 002bf1ac: jal 0x002d43a4 */ set(31,UINT64_C(0x002bf1b4));/* delay 002bf1b0 */ set(6,cpu(19));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002d43a4),UINT32_C(0x002bf1ac));
/* 002bf1b4: addu v1,s2,s3 */ set(3,sx((uint32_t)cpu(18)+(uint32_t)cpu(19)));
/* 002bf1b8: b 0x002bf1e0 */ /* delay 002bf1bc */ sb(ea(3,(int32_t)UINT32_C(0x00000005)),(uint8_t)cpu(0));goto L_002bf1e0;
L_002bf1c0:;
/* 002bf1c0: jal 0x002a8af8 */ set(31,UINT64_C(0x002bf1c8));/* delay 002bf1c4 */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a8af8),UINT32_C(0x002bf1c0));
/* 002bf1c8: move a1,s4 */ set(5,cpu(20));
/* 002bf1cc: move s2,v0 */ set(18,cpu(2));
/* 002bf1d0: jal 0x002d5bf8 */ set(31,UINT64_C(0x002bf1d8));/* delay 002bf1d4 */ set(4,cpu(18));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002d5bf8),UINT32_C(0x002bf1d0));
/* 002bf1d8: b 0x002bf1e4 */ /* delay 002bf1dc */ set(2,cpu(18));goto L_002bf1e4;
L_002bf1e0:;
/* 002bf1e0: move v0,s2 */ set(2,cpu(18));
L_002bf1e4:;
/* 002bf1e4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002bf1e8:;
/* 002bf1e8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bf1ec: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf1f0: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002bf1f4: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002bf1f8: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002bf1fc: jr ra */ {uint64_t target=cpu(31);/* delay 002bf200 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002bf208(void){
uint64_t incoming=cpu(31);
/* 002bf208: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002bf20c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf210: move s2,a1 */ set(18,cpu(5));
/* 002bf214: li a1,0x3a */ set(5,sx(UINT32_C(0x0000003a)));
/* 002bf218: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bf21c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bf220: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002bf224: jal 0x002d5924 */ set(31,UINT64_C(0x002bf22c));/* delay 002bf228 */ set(17,cpu(4));body_002d5924();
/* 002bf22c: beq v0,zero,0x002bf2f8 */ {int taken=(cpu(2)==cpu(0));/* delay 002bf230 */ set(5,sx(UINT32_C(0x00550000)));if(taken){goto L_002bf2f8;}}
/* 002bf234: move a0,s1 */ set(4,cpu(17));
/* 002bf238: addiu a1,a1,0x1968 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00001968)));
/* 002bf23c: jal 0x002d4310 */ set(31,UINT64_C(0x002bf244));/* delay 002bf240 */ set(6,sx(UINT32_C(0x00000007)));body_002d4310();
/* 002bf244: bne v0,zero,0x002bf280 */ {int taken=(cpu(2)!=cpu(0));/* delay 002bf248 */ set(5,sx(UINT32_C(0x00550000)));if(taken){goto L_002bf280;}}
/* 002bf24c: lui a1,0x55 */ set(5,sx(UINT32_C(0x00550000)));
/* 002bf250: addiu a0,s1,0x7 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000007)));
/* 002bf254: addiu a1,a1,0x1980 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00001980)));
/* 002bf258: jal 0x002d4310 */ set(31,UINT64_C(0x002bf260));/* delay 002bf25c */ set(6,sx(UINT32_C(0x00000007)));body_002d4310();
/* 002bf260: bnel v0,zero,0x002bf278 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002bf264 */ set(16,cpu(0));goto L_002bf278;}}
/* 002bf268: li s0,0x3 */ set(16,sx(UINT32_C(0x00000003)));
/* 002bf26c: b 0x002bf2f0 */ /* delay 002bf270 */ set(4,cpu(0));goto L_002bf2f0;
L_002bf278:;
/* 002bf278: b 0x002bf2f0 */ /* delay 002bf27c */ set(4,sx(UINT32_C(0x00000007)));goto L_002bf2f0;
L_002bf280:;
/* 002bf280: move a0,s1 */ set(4,cpu(17));
/* 002bf284: addiu a1,a1,0x1970 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00001970)));
/* 002bf288: jal 0x002d4310 */ set(31,UINT64_C(0x002bf290));/* delay 002bf28c */ set(6,sx(UINT32_C(0x00000006)));body_002d4310();
/* 002bf290: bne v0,zero,0x002bf2a8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002bf294 */ set(5,sx(UINT32_C(0x00550000)));if(taken){goto L_002bf2a8;}}
/* 002bf298: li s0,0x1 */ set(16,sx(UINT32_C(0x00000001)));
/* 002bf29c: b 0x002bf2f0 */ /* delay 002bf2a0 */ set(4,sx(UINT32_C(0x00000006)));goto L_002bf2f0;
L_002bf2a8:;
/* 002bf2a8: move a0,s1 */ set(4,cpu(17));
/* 002bf2ac: addiu a1,a1,0x1978 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00001978)));
/* 002bf2b0: jal 0x002d4310 */ set(31,UINT64_C(0x002bf2b8));/* delay 002bf2b4 */ set(6,sx(UINT32_C(0x00000005)));body_002d4310();
/* 002bf2b8: bne v0,zero,0x002bf2d0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002bf2bc */ set(5,sx(UINT32_C(0x00550000)));if(taken){goto L_002bf2d0;}}
/* 002bf2c0: li s0,0x2 */ set(16,sx(UINT32_C(0x00000002)));
/* 002bf2c4: b 0x002bf2f0 */ /* delay 002bf2c8 */ set(4,sx(UINT32_C(0x00000005)));goto L_002bf2f0;
L_002bf2d0:;
/* 002bf2d0: move a0,s1 */ set(4,cpu(17));
/* 002bf2d4: addiu a1,a1,0x1988 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00001988)));
/* 002bf2d8: jal 0x002d4310 */ set(31,UINT64_C(0x002bf2e0));/* delay 002bf2dc */ set(6,sx(UINT32_C(0x00000006)));body_002d4310();
/* 002bf2e0: bne v0,zero,0x002bf310 */ {int taken=(cpu(2)!=cpu(0));/* delay 002bf2e4 */ set(2,sx(UINT32_C(0xffffffff)));if(taken){goto L_002bf310;}}
/* 002bf2e8: li s0,0x3 */ set(16,sx(UINT32_C(0x00000003)));
/* 002bf2ec: li a0,0x6 */ set(4,sx(UINT32_C(0x00000006)));
L_002bf2f0:;
/* 002bf2f0: b 0x002bf300 */ /* delay 002bf2f4 */ set(4,sx((uint32_t)cpu(17)+(uint32_t)cpu(4)));goto L_002bf300;
L_002bf2f8:;
/* 002bf2f8: lbu s0,-0x2812(gp) */ set(16,byte(ea(28,(int32_t)UINT32_C(0xffffd7ee))));
/* 002bf2fc: move a0,s1 */ set(4,cpu(17));
L_002bf300:;
/* 002bf300: jal 0x002befc0 */ set(31,UINT64_C(0x002bf308));/* delay 002bf304 */ set(5,cpu(16));body_002befc0();
/* 002bf308: sw v0,0x0(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002bf30c: move v0,s0 */ set(2,cpu(16));
L_002bf310:;
/* 002bf310: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bf314: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bf318: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf31c: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002bf320: jr ra */ {uint64_t target=cpu(31);/* delay 002bf324 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002bf328(void){
uint64_t incoming=cpu(31);
/* 002bf328: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002bf32c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002bf330: move s3,a0 */ set(19,cpu(4));
/* 002bf334: li a0,0x40 */ set(4,sx(UINT32_C(0x00000040)));
/* 002bf338: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bf33c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bf340: move s1,a1 */ set(17,cpu(5));
/* 002bf344: move s0,t0 */ set(16,cpu(8));
/* 002bf348: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf34c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002bf350: move s4,a3 */ set(20,cpu(7));
/* 002bf354: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002bf358: jal 0x002a8ba8 */ set(31,UINT64_C(0x002bf360));/* delay 002bf35c */ set(18,cpu(6));body_002a8ba8();
/* 002bf360: li a0,-0x1 */ set(4,sx(UINT32_C(0xffffffff)));
/* 002bf364: move v1,v0 */ set(3,cpu(2));
/* 002bf368: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002bf36c: sw s0,0x3c(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(16));
/* 002bf370: sw s3,0x10(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(19));
/* 002bf374: sb s1,0x14(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000014)),(uint8_t)cpu(17));
/* 002bf378: sb s2,0x15(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000015)),(uint8_t)cpu(18));
/* 002bf37c: sw s4,0x38(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(20));
/* 002bf380: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bf384: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bf388: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf38c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002bf390: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002bf394: sw a0,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(4));
/* 002bf398: sb zero,0x16(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(0));
/* 002bf39c: jr ra */ {uint64_t target=cpu(31);/* delay 002bf3a0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002bf3a8(void){
uint64_t incoming=cpu(31);
/* 002bf3a8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002bf3ac: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002bf3b0: move s1,a1 */ set(17,cpu(5));
/* 002bf3b4: move a1,sp */ set(5,cpu(29));
/* 002bf3b8: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf3bc: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002bf3c0: jal 0x002bf208 */ set(31,UINT64_C(0x002bf3c8));/* delay 002bf3c4 */ set(16,cpu(6));body_002bf208();
/* 002bf3c8: move a3,s1 */ set(7,cpu(17));
/* 002bf3cc: move v1,v0 */ set(3,cpu(2));
/* 002bf3d0: move v0,zero */ set(2,cpu(0));
/* 002bf3d4: move a1,v1 */ set(5,cpu(3));
/* 002bf3d8: move t0,s0 */ set(8,cpu(16));
/* 002bf3dc: bltz v1,0x002bf3fc */ {int taken=((int64_t)cpu(3)<0);/* delay 002bf3e0 */ set(6,sx(UINT32_C(0x00000001)));if(taken){goto L_002bf3fc;}}
/* 002bf3e4: jal 0x002bf328 */ set(31,UINT64_C(0x002bf3ec));/* delay 002bf3e8 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000000)));body_002bf328();
/* 002bf3ec: move s0,v0 */ set(16,cpu(2));
/* 002bf3f0: jal 0x002be5b8 */ set(31,UINT64_C(0x002bf3f8));/* delay 002bf3f4 */ set(4,cpu(16));body_002be5b8();
/* 002bf3f8: move v0,s0 */ set(2,cpu(16));
L_002bf3fc:;
/* 002bf3fc: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf400: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002bf404: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002bf408: jr ra */ {uint64_t target=cpu(31);/* delay 002bf40c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002bf8f0(void){
uint64_t incoming=cpu(31);
/* 002bf8f0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002bf8f4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bf8f8: move s1,a0 */ set(17,cpu(4));
/* 002bf8fc: sll v0,s1,0x1 */ set(2,sx((uint32_t)cpu(17)<<1));
/* 002bf900: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bf904: addu v0,v0,s1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(17)));
/* 002bf908: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf90c: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 002bf910: lui s0,0x53 */ set(16,sx(UINT32_C(0x00530000)));
/* 002bf914: addiu s0,s0,-0x6500 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffff9b00)));
/* 002bf918: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 002bf91c: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002bf920: bgez v0,0x002bf988 */ {int taken=((int64_t)cpu(2)>=0);/* delay 002bf924 */ set(4,cpu(0));if(taken){goto L_002bf988;}}
/* 002bf928: li a1,0xff */ set(5,sx(UINT32_C(0x000000ff)));
/* 002bf92c: jal 0x002a8080 */ set(31,UINT64_C(0x002bf934));/* delay 002bf930 */ set(6,cpu(0));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a8080),UINT32_C(0x002bf92c));
/* 002bf934: li a1,0x4000 */ set(5,sx(UINT32_C(0x00004000)));
/* 002bf938: lui v1,0x2c */ set(3,sx(UINT32_C(0x002c0000)));
/* 002bf93c: li a0,0x3 */ set(4,sx(UINT32_C(0x00000003)));
/* 002bf940: li a2,0x48 */ set(6,sx(UINT32_C(0x00000048)));
/* 002bf944: addiu v1,v1,-0x12b0 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffed50)));
/* 002bf948: beq s1,a0,0x002bf958 */ {int taken=(cpu(17)==cpu(4));/* delay 002bf94c */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));if(taken){goto L_002bf958;}}
/* 002bf950: lui v0,0x2c */ set(2,sx(UINT32_C(0x002c0000)));
/* 002bf954: addiu v1,v0,-0x1738 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0xffffe8c8)));
L_002bf958:;
/* 002bf958: move a0,v1 */ set(4,cpu(3));
/* 002bf95c: li v0,0x48 */ set(2,sx(UINT32_C(0x00000048)));
/* 002bf960: jal 0x002a8120 */ set(31,UINT64_C(0x002bf968));/* delay 002bf964 */ sw(ea(28,(int32_t)UINT32_C(0xffffd7f0)),(uint32_t)cpu(2));body_002a8120();
/* 002bf968: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002bf96c: move a1,s0 */ set(5,cpu(16));
/* 002bf970: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bf974: move a0,v0 */ set(4,cpu(2));
/* 002bf978: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bf97c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf980: j 0x002dbcc0 */ /* delay 002bf984 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002dbcc0),UINT32_C(0x002bf980));return;
L_002bf988:;
/* 002bf988: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bf98c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bf990: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf994: jr ra */ {uint64_t target=cpu(31);/* delay 002bf998 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002bfce8(void){
uint64_t incoming=cpu(31);
/* 002bfce8: slti v0,a1,0x4 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000004));
/* 002bfcec: bne v0,zero,0x002bfd14 */ {int taken=(cpu(2)!=cpu(0));/* delay 002bfcf0 */ set(3,cpu(4));if(taken){goto L_002bfd14;}}
L_002bfcf4:;
/* 002bfcf4: addiu a1,a1,-0x4 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xfffffffc)));
/* 002bfcf8: slti v0,a1,0x4 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000004));
/* 002bfcfc: sq zero,0x0(v1) */ sq(0,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002bfd00: sq zero,0x10(v1) */ sq(0,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 002bfd04: sq zero,0x20(v1) */ sq(0,ea(3,(int32_t)UINT32_C(0x00000020)));
/* 002bfd08: sq zero,0x30(v1) */ sq(0,ea(3,(int32_t)UINT32_C(0x00000030)));
/* 002bfd0c: beq v0,zero,0x002bfcf4 */ {int taken=(cpu(2)==cpu(0));/* delay 002bfd10 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000040)));if(taken){goto L_002bfcf4;}}
L_002bfd14:;
/* 002bfd14: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 002bfd18: beq a1,v0,0x002bfd4c */ {int taken=(cpu(5)==cpu(2));/* delay 002bfd1c */ if(taken){goto L_002bfd4c;}}
/* 002bfd20: slti v0,a1,0x3 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000003));
/* 002bfd24: beq v0,zero,0x002bfd40 */ {int taken=(cpu(2)==cpu(0));/* delay 002bfd28 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_002bfd40;}}
/* 002bfd2c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002bfd30: beq a1,v0,0x002bfd50 */ {int taken=(cpu(5)==cpu(2));/* delay 002bfd34 */ if(taken){goto L_002bfd50;}}
/* 002bfd38: jr ra */ {uint64_t target=cpu(31);/* delay 002bfd3c */ set(2,cpu(4));checkReturn(target,incoming);return;}
L_002bfd40:;
/* 002bfd40: bnel a1,v0,0x002bfd58 */ {int taken=(cpu(5)!=cpu(2));if(taken){/* delay 002bfd44 */ set(2,cpu(4));goto L_002bfd58;}}
/* 002bfd48: sq zero,0x20(v1) */ sq(0,ea(3,(int32_t)UINT32_C(0x00000020)));
L_002bfd4c:;
/* 002bfd4c: sq zero,0x10(v1) */ sq(0,ea(3,(int32_t)UINT32_C(0x00000010)));
L_002bfd50:;
/* 002bfd50: sq zero,0x0(v1) */ sq(0,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002bfd54: move v0,a0 */ set(2,cpu(4));
L_002bfd58:;
/* 002bfd58: jr ra */ {uint64_t target=cpu(31);/* delay 002bfd5c */ checkReturn(target,incoming);return;}
}
static void body_002bfd60(void){
uint64_t incoming=cpu(31);
/* 002bfd60: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002bfd64: move v0,zero */ set(2,cpu(0));
/* 002bfd68: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bfd6c: move s2,a0 */ set(18,cpu(4));
/* 002bfd70: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bfd74: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bfd78: beq s2,zero,0x002bfdb4 */ {int taken=(cpu(18)==cpu(0));/* delay 002bfd7c */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));if(taken){goto L_002bfdb4;}}
/* 002bfd80: jal 0x002d5d0c */ set(31,UINT64_C(0x002bfd88));/* delay 002bfd84 */ nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002d5d0c),UINT32_C(0x002bfd80));
/* 002bfd88: move s0,v0 */ set(16,cpu(2));
/* 002bfd8c: jal 0x002a8af8 */ set(31,UINT64_C(0x002bfd94));/* delay 002bfd90 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a8af8),UINT32_C(0x002bfd8c));
/* 002bfd94: move a1,s2 */ set(5,cpu(18));
/* 002bfd98: move s1,v0 */ set(17,cpu(2));
/* 002bfd9c: move a2,s0 */ set(6,cpu(16));
/* 002bfda0: move a0,s1 */ set(4,cpu(17));
/* 002bfda4: jal 0x002d43a4 */ set(31,UINT64_C(0x002bfdac));/* delay 002bfda8 */ set(16,sx((uint32_t)cpu(17)+(uint32_t)cpu(16)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002d43a4),UINT32_C(0x002bfda4));
/* 002bfdac: sb zero,0x0(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));
/* 002bfdb0: move v0,s1 */ set(2,cpu(17));
L_002bfdb4:;
/* 002bfdb4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bfdb8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bfdbc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bfdc0: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002bfdc4: jr ra */ {uint64_t target=cpu(31);/* delay 002bfdc8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002c2070(void){
uint64_t incoming=cpu(31);
/* 002c2070: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c2074: move a1,zero */ set(5,cpu(0));
/* 002c2078: sw a0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 002c207c: li a0,0xd0 */ set(4,sx(UINT32_C(0x000000d0)));
/* 002c2080: move a2,sp */ set(6,cpu(29));
/* 002c2084: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c2088: jal 0x002c10e8 */ set(31,UINT64_C(0x002c2090));/* delay 002c208c */ set(7,sx(UINT32_C(0x00000010)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002c10e8),UINT32_C(0x002c2088));
/* 002c2090: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c2094: jr ra */ {uint64_t target=cpu(31);/* delay 002c2098 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002c6030(void){
uint64_t incoming=cpu(31);
/* 002c6030: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c6034: li a2,0x38 */ set(6,sx(UINT32_C(0x00000038)));
/* 002c6038: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c603c: move s1,a1 */ set(17,cpu(5));
/* 002c6040: move a1,zero */ set(5,cpu(0));
/* 002c6044: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6048: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c604c: jal 0x002d4558 */ set(31,UINT64_C(0x002c6054));/* delay 002c6050 */ set(16,cpu(4));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002d4558),UINT32_C(0x002c604c));
/* 002c6054: lui v1,0x2c */ set(3,sx(UINT32_C(0x002c0000)));
/* 002c6058: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002c605c: addiu v1,v1,0x64b0 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x000064b0)));
/* 002c6060: beq s1,zero,0x002c6070 */ {int taken=(cpu(17)==cpu(0));/* delay 002c6064 */ sh(ea(16,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(2));if(taken){goto L_002c6070;}}
/* 002c6068: b 0x002c6074 */ /* delay 002c606c */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(17));goto L_002c6074;
L_002c6070:;
/* 002c6070: sw v1,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
L_002c6074:;
/* 002c6074: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6078: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c607c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6080: jr ra */ {uint64_t target=cpu(31);/* delay 002c6084 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002c6098(void){
uint64_t incoming=cpu(31);
/* 002c6098: lbu v0,0x1(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000001))));
/* 002c609c: ori v0,v0,0x2 */ set(2,cpu(2)|UINT32_C(0x00000002));
/* 002c60a0: jr ra */ {uint64_t target=cpu(31);/* delay 002c60a4 */ sb(ea(4,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_002c60a8(void){
uint64_t incoming=cpu(31);
/* 002c60a8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c60ac: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c60b0: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c60b4: lw s0,0x30(a0) */ lw(16,ea(4,(int32_t)UINT32_C(0x00000030)));
/* 002c60b8: beq s0,zero,0x002c60d0 */ {int taken=(cpu(16)==cpu(0));/* delay 002c60bc */ set(4,cpu(16));if(taken){goto L_002c60d0;}}
L_002c60c0:;
/* 002c60c0: jal 0x002a8bd8 */ set(31,UINT64_C(0x002c60c8));/* delay 002c60c4 */ lw(16,ea(16,(int32_t)UINT32_C(0x00000000)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a8bd8),UINT32_C(0x002c60c0));
/* 002c60c8: bne s0,zero,0x002c60c0 */ {int taken=(cpu(16)!=cpu(0));/* delay 002c60cc */ set(4,cpu(16));if(taken){goto L_002c60c0;}}
L_002c60d0:;
/* 002c60d0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c60d4: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c60d8: jr ra */ {uint64_t target=cpu(31);/* delay 002c60dc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002d4310(void){
uint64_t incoming=cpu(31);
/* 002d4310: sltiu v0,a2,0x10 */ set(2,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000010));
/* 002d4314: bne v0,zero,0x002d435c */ {int taken=(cpu(2)!=cpu(0));/* delay 002d4318 */ set(2,cpu(4)|cpu(5));if(taken){goto L_002d435c;}}
/* 002d431c: andi v0,v0,0xf */ set(2,cpu(2)&UINT32_C(0x0000000f));
/* 002d4320: bne v0,zero,0x002d435c */ {int taken=(cpu(2)!=cpu(0));/* delay 002d4324 */ if(taken){goto L_002d435c;}}
L_002d4328:;
/* 002d4328: lq v1,0x0(a0) */ requestLq(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002d432c: sltiu a3,a2,0x20 */ set(7,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000020));
/* 002d4330: lq v0,0x0(a1) */ requestLq(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d4334: addiu a0,a0,0x10 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000010)));
/* 002d4338: pxor t0,v0,v1 */ requestPacked(5,8,2,3);
/* 002d433c: addiu v0,a1,0x10 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x00000010)));
/* 002d4340: pcpyud t2,t0,a3 */ requestPacked(1,10,8,7);
/* 002d4344: or t1,t2,t0 */ set(9,cpu(10)|cpu(8));
/* 002d4348: movz a1,v0,t1 */ if(cpu(9)==0){set(5,cpu(2));}
/* 002d434c: bnel t1,zero,0x002d435c */ {int taken=(cpu(9)!=cpu(0));if(taken){/* delay 002d4350 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffffff0)));goto L_002d435c;}}
/* 002d4354: beq a3,zero,0x002d4328 */ {int taken=(cpu(7)==cpu(0));/* delay 002d4358 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xfffffff0)));if(taken){goto L_002d4328;}}
L_002d435c:;
/* 002d435c: lui v0,0xffff */ set(2,sx(UINT32_C(0xffff0000)));
/* 002d4360: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 002d4364: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002d4368: beq a2,v0,0x002d439c */ {int taken=(cpu(6)==cpu(2));/* delay 002d436c */ if(taken){goto L_002d439c;}}
/* 002d4370: lui a3,0xffff */ set(7,sx(UINT32_C(0xffff0000)));
/* 002d4374: ori a3,a3,0xffff */ set(7,cpu(7)|UINT32_C(0x0000ffff));
L_002d4378:;
/* 002d4378: lbu v1,0x0(a0) */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 002d437c: lbu v0,0x0(a1) */ set(2,byte(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 002d4380: beq v1,v0,0x002d4390 */ {int taken=(cpu(3)==cpu(2));/* delay 002d4384 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));if(taken){goto L_002d4390;}}
/* 002d4388: jr ra */ {uint64_t target=cpu(31);/* delay 002d438c */ set(2,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));checkReturn(target,incoming);return;}
L_002d4390:;
/* 002d4390: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 002d4394: bne a2,a3,0x002d4378 */ {int taken=(cpu(6)!=cpu(7));/* delay 002d4398 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));if(taken){goto L_002d4378;}}
L_002d439c:;
/* 002d439c: jr ra */ {uint64_t target=cpu(31);/* delay 002d43a0 */ set(2,cpu(0));checkReturn(target,incoming);return;}
}
static void body_002d5924(void){
uint64_t incoming=cpu(31);
/* 002d5924: andi v0,a0,0x7 */ set(2,cpu(4)&UINT32_C(0x00000007));
/* 002d5928: bne v0,zero,0x002d5a94 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d592c */ set(5,cpu(5)&UINT32_C(0x000000ff));if(taken){goto L_002d5a94;}}
/* 002d5930: dsll v1,a1,0x8 */ set(3,cpu(5)<<8);
/* 002d5934: lui a2,0x101 */ set(6,sx(UINT32_C(0x01010000)));
/* 002d5938: ori a2,a2,0x101 */ set(6,cpu(6)|UINT32_C(0x00000101));
/* 002d593c: dsll a2,a2,0x10 */ set(6,cpu(6)<<16);
/* 002d5940: ori a2,a2,0x101 */ set(6,cpu(6)|UINT32_C(0x00000101));
/* 002d5944: dsll a2,a2,0x10 */ set(6,cpu(6)<<16);
/* 002d5948: ori a2,a2,0x101 */ set(6,cpu(6)|UINT32_C(0x00000101));
/* 002d594c: daddu t2,v1,a1 */ set(10,cpu(3)+cpu(5));
/* 002d5950: andi v1,a0,0xf */ set(3,cpu(4)&UINT32_C(0x0000000f));
/* 002d5954: dsll v0,t2,0x10 */ set(2,cpu(10)<<16);
/* 002d5958: lui t0,0x8080 */ set(8,sx(UINT32_C(0x80800000)));
/* 002d595c: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 002d5960: dsll t0,t0,0x10 */ set(8,cpu(8)<<16);
/* 002d5964: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 002d5968: dsll t0,t0,0x10 */ set(8,cpu(8)<<16);
/* 002d596c: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 002d5970: daddu v0,v0,t2 */ set(2,cpu(2)+cpu(10));
/* 002d5974: dsll32 t2,v0,0x0 */ set(10,cpu(2)<<32);
/* 002d5978: bne v1,zero,0x002d5a0c */ {int taken=(cpu(3)!=cpu(0));/* delay 002d597c */ set(7,cpu(2)+cpu(10));if(taken){goto L_002d5a0c;}}
L_002d5980:;
/* 002d5980: lq t1,0x0(a0) */ requestLq(9,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002d5984: pcpyld t2,a2,a2 */ requestPacked(0,10,6,6);
/* 002d5988: pnor v1,zero,t1 */ requestPacked(3,3,0,9);
/* 002d598c: psubb v0,t1,t2 */ requestPacked(4,2,9,10);
/* 002d5990: pcpyld a2,t0,t0 */ requestPacked(0,6,8,8);
/* 002d5994: pand v0,v0,v1 */ requestPacked(2,2,2,3);
/* 002d5998: pcpyld t0,a3,a3 */ requestPacked(0,8,7,7);
/* 002d599c: pand v0,v0,a2 */ requestPacked(2,2,2,6);
/* 002d59a0: pcpyud v1,v0,a3 */ requestPacked(1,3,2,7);
/* 002d59a4: or v1,v0,v1 */ set(3,cpu(2)|cpu(3));
/* 002d59a8: bnel v1,zero,0x002d5a98 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 002d59ac */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_002d5a98;}}
/* 002d59b0: pxor v0,t1,t0 */ requestPacked(5,2,9,8);
/* 002d59b4: psubb v1,v0,t2 */ requestPacked(4,3,2,10);
/* 002d59b8: pnor v0,zero,v0 */ requestPacked(3,2,0,2);
/* 002d59bc: lui t0,0x8080 */ set(8,sx(UINT32_C(0x80800000)));
/* 002d59c0: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 002d59c4: dsll t0,t0,0x10 */ set(8,cpu(8)<<16);
/* 002d59c8: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 002d59cc: dsll t0,t0,0x10 */ set(8,cpu(8)<<16);
/* 002d59d0: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 002d59d4: pand v1,v1,v0 */ requestPacked(2,3,3,2);
/* 002d59d8: pand v1,v1,a2 */ requestPacked(2,3,3,6);
/* 002d59dc: lui a2,0x101 */ set(6,sx(UINT32_C(0x01010000)));
/* 002d59e0: ori a2,a2,0x101 */ set(6,cpu(6)|UINT32_C(0x00000101));
/* 002d59e4: dsll a2,a2,0x10 */ set(6,cpu(6)<<16);
/* 002d59e8: ori a2,a2,0x101 */ set(6,cpu(6)|UINT32_C(0x00000101));
/* 002d59ec: dsll a2,a2,0x10 */ set(6,cpu(6)<<16);
/* 002d59f0: ori a2,a2,0x101 */ set(6,cpu(6)|UINT32_C(0x00000101));
/* 002d59f4: pcpyud v0,v1,a1 */ requestPacked(1,2,3,5);
/* 002d59f8: or v1,v0,v1 */ set(3,cpu(2)|cpu(3));
/* 002d59fc: beql v1,zero,0x002d5980 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 002d5a00 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000010)));goto L_002d5980;}}
/* 002d5a04: b 0x002d5a98 */ /* delay 002d5a08 */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_002d5a98;
L_002d5a0c:;
/* 002d5a0c: ld t1,0x0(a0) */ restore(9,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002d5a10: nor v1,zero,t1 */ set(3,~(cpu(0)|cpu(9)));
/* 002d5a14: dsubu v0,t1,a2 */ set(2,cpu(9)-cpu(6));
/* 002d5a18: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002d5a1c: and v0,v0,t0 */ set(2,cpu(2)&cpu(8));
/* 002d5a20: bnel v0,zero,0x002d5a98 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d5a24 */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_002d5a98;}}
/* 002d5a28: xor v0,t1,a3 */ set(2,cpu(9)^cpu(7));
/* 002d5a2c: dsubu v1,v0,a2 */ set(3,cpu(2)-cpu(6));
/* 002d5a30: nor v0,zero,v0 */ set(2,~(cpu(0)|cpu(2)));
/* 002d5a34: and v1,v1,v0 */ set(3,cpu(3)&cpu(2));
/* 002d5a38: and v1,v1,t0 */ set(3,cpu(3)&cpu(8));
/* 002d5a3c: bnel v1,zero,0x002d5a98 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 002d5a40 */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_002d5a98;}}
/* 002d5a44: move t1,a2 */ set(9,cpu(6));
/* 002d5a48: addiu a0,a0,0x8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000008)));
L_002d5a4c:;
/* 002d5a4c: ld a2,0x0(a0) */ restore(6,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002d5a50: dsubu v0,a2,t1 */ set(2,cpu(6)-cpu(9));
/* 002d5a54: nor v1,zero,a2 */ set(3,~(cpu(0)|cpu(6)));
/* 002d5a58: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002d5a5c: and v0,v0,t0 */ set(2,cpu(2)&cpu(8));
/* 002d5a60: bne v0,zero,0x002d5a94 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d5a64 */ set(2,cpu(6)^cpu(7));if(taken){goto L_002d5a94;}}
/* 002d5a68: nor v1,zero,v0 */ set(3,~(cpu(0)|cpu(2)));
/* 002d5a6c: dsubu v0,v0,t1 */ set(2,cpu(2)-cpu(9));
/* 002d5a70: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002d5a74: and v0,v0,t0 */ set(2,cpu(2)&cpu(8));
/* 002d5a78: beql v0,zero,0x002d5a4c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d5a7c */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000008)));goto L_002d5a4c;}}
/* 002d5a80: b 0x002d5a98 */ /* delay 002d5a84 */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_002d5a98;
L_002d5a88:;
/* 002d5a88: beql v0,a1,0x002d5aa4 */ {int taken=(cpu(2)==cpu(5));if(taken){/* delay 002d5a8c */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_002d5aa4;}}
/* 002d5a90: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
L_002d5a94:;
/* 002d5a94: lbu v0,0x0(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
L_002d5a98:;
/* 002d5a98: bne v0,zero,0x002d5a88 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d5a9c */ if(taken){goto L_002d5a88;}}
/* 002d5aa0: lbu v1,0x0(a0) */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
L_002d5aa4:;
/* 002d5aa4: move v0,zero */ set(2,cpu(0));
/* 002d5aa8: xor v1,v1,a1 */ set(3,cpu(3)^cpu(5));
/* 002d5aac: jr ra */ {uint64_t target=cpu(31);/* delay 002d5ab0 */ if(cpu(3)==0){set(2,cpu(4));}checkReturn(target,incoming);return;}
}
uint32_t nocturneBattleRewardLifecycleDependencyBody(uint32_t entry){switch(entry){
case UINT32_C(0x001009e8):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001009e8();return 1u;case UINT32_C(0x00100a48):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00100a48();return 1u;case UINT32_C(0x00100c48):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00100c48();return 1u;case UINT32_C(0x00100d70):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00100d70();return 1u;case UINT32_C(0x00100e08):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00100e08();return 1u;case UINT32_C(0x00100e80):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00100e80();return 1u;case UINT32_C(0x00101aa0):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00101aa0();return 1u;case UINT32_C(0x00105048):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00105048();return 1u;case UINT32_C(0x0010dcb8):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0010dcb8();return 1u;case UINT32_C(0x0010e548):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0010e548();return 1u;case UINT32_C(0x0010e588):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0010e588();return 1u;case UINT32_C(0x0010e610):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0010e610();return 1u;case UINT32_C(0x001275d0):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001275d0();return 1u;case UINT32_C(0x00296648):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00296648();return 1u;case UINT32_C(0x002966a8):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002966a8();return 1u;case UINT32_C(0x00296738):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00296738();return 1u;case UINT32_C(0x002968f8):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002968f8();return 1u;case UINT32_C(0x00296b08):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00296b08();return 1u;case UINT32_C(0x00297460):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00297460();return 1u;case UINT32_C(0x002a8120):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002a8120();return 1u;case UINT32_C(0x002a8170):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002a8170();return 1u;case UINT32_C(0x002a8ba8):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002a8ba8();return 1u;case UINT32_C(0x002a9650):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002a9650();return 1u;case UINT32_C(0x002be5b8):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002be5b8();return 1u;case UINT32_C(0x002befc0):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002befc0();return 1u;case UINT32_C(0x002bf208):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002bf208();return 1u;case UINT32_C(0x002bf328):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002bf328();return 1u;case UINT32_C(0x002bf3a8):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002bf3a8();return 1u;case UINT32_C(0x002bf8f0):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002bf8f0();return 1u;case UINT32_C(0x002bfce8):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002bfce8();return 1u;case UINT32_C(0x002bfd60):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002bfd60();return 1u;case UINT32_C(0x002c2070):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002c2070();return 1u;case UINT32_C(0x002c6030):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002c6030();return 1u;case UINT32_C(0x002c6098):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002c6098();return 1u;case UINT32_C(0x002c60a8):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002c60a8();return 1u;case UINT32_C(0x002d4310):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002d4310();return 1u;case UINT32_C(0x002d5924):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002d5924();return 1u;
default:return 0u;}}
uint64_t ps2BattleRewardLifecycleDependency_001009E8(void){body_001009e8();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_00100A48(void){body_00100a48();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_00100C48(void){body_00100c48();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_00100D70(void){body_00100d70();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_00100E08(void){body_00100e08();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_00100E80(void){body_00100e80();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_00101AA0(void){body_00101aa0();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_00105048(void){body_00105048();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_0010DCB8(void){body_0010dcb8();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_0010E548(void){body_0010e548();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_0010E588(void){body_0010e588();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_0010E610(void){body_0010e610();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_001275D0(void){body_001275d0();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_00296648(void){body_00296648();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_002966A8(void){body_002966a8();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_00296738(void){body_00296738();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_002968F8(void){body_002968f8();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_00296B08(void){body_00296b08();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_00297460(void){body_00297460();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_002A8BA8(void){body_002a8ba8();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_002A9650(void){body_002a9650();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_002A8120(void){body_002a8120();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_002A8170(void){body_002a8170();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_002BF3A8(void){body_002bf3a8();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_002BE5B8(void){body_002be5b8();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_002BF208(void){body_002bf208();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_002BF328(void){body_002bf328();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_002BEFC0(void){body_002befc0();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_002BF8F0(void){body_002bf8f0();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_002BFCE8(void){body_002bfce8();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_002BFD60(void){body_002bfd60();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_002C2070(void){body_002c2070();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_002C6030(void){body_002c6030();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_002C6098(void){body_002c6098();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_002C60A8(void){body_002c60a8();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_002D5924(void){body_002d5924();return cpu(2);}
uint64_t ps2BattleRewardLifecycleDependency_002D4310(void){body_002d4310();return cpu(2);}
