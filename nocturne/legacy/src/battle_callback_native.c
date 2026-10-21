/* Complete original parents17/86. Fixed native operations, guest frames,
 * precise callback masks. This unit has NO callback or formatter provider. */
#include "battle_callback_native.h"
#include "process_lists.h"
#include "battle_stock_renderer.h"
#include "battle_action_sequence.h"
#include "battle_action_process.h"
#include <stdlib.h>
#include <string.h>
typedef struct BattleCallbackNativeValues {uint64_t r[32];} BattleCallbackNativeValues;
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t sar(uint32_t v,unsigned n){return sx(n==0?v:(v>>n)|((v&UINT32_C(0x80000000))?(UINT32_MAX<<(32u-n)):0u));}
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleCallbackNativeAddress(a);}
static uint16_t hword(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint64_t quad(uint32_t a){uint64_t v;memcpy(&v,at(a),8);return v;}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sd(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
static BattleCallbackNativeBoundary boundary(const BattleCallbackNativeValues *c,uint32_t pc,uint32_t mask){
 BattleCallbackNativeBoundary b={pc,mask,
  (mask&(UINT32_C(1)<<2))?c->r[2]:0,(mask&(UINT32_C(1)<<3))?c->r[3]:0,
  (mask&(UINT32_C(1)<<4))?c->r[4]:0,(mask&(UINT32_C(1)<<5))?c->r[5]:0,
  (mask&(UINT32_C(1)<<16))?c->r[16]:0,(mask&(UINT32_C(1)<<17))?c->r[17]:0,
  (mask&(UINT32_C(1)<<29))?c->r[29]:0,(mask&(UINT32_C(1)<<31))?c->r[31]:0};return b;
}
static BattleCallbackNativeValues begin(void){BattleCallbackNativeValues c={0};
 c.r[16]=nocturneBattleCallbackNativeReadGpr(16);c.r[17]=nocturneBattleCallbackNativeReadGpr(17);
 c.r[28]=nocturneBattleCallbackNativeReadGpr(28);c.r[31]=nocturneBattleCallbackNativeReadGpr(31);
 c.r[29]=nocturneBattleCallbackNativeStackPointer();return c;
}
static void body_00257c80(BattleCallbackNativeValues *c,uint32_t inherited_mask);
static void body_00257cd0(BattleCallbackNativeValues *c);

static void body_00257c80(BattleCallbackNativeValues *c,uint32_t inherited_mask){
/* 00257c80: move v1,a0 */ c->r[3]=c->r[4];
/* 00257c84: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 00257c88: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 00257c8c: sb a1,0x8(v1) */ *at((uint32_t)c->r[3]+UINT32_C(0x00000008))=(uint8_t)c->r[5];
/* 00257c90: sll a1,a1,0x18 */ c->r[5]=sx((uint32_t)c->r[5]<<24u);
/* 00257c94: sb zero,0x9(v1) */ *at((uint32_t)c->r[3]+UINT32_C(0x00000009))=(uint8_t)c->r[0];
/* 00257c98: sra a1,a1,0x15 */ c->r[5]=sar((uint32_t)c->r[5],21u);
/* 00257c9c: sw zero,0xc(v1) */ sw((uint32_t)c->r[3]+UINT32_C(0x0000000c),(uint32_t)c->r[0]);
/* 00257ca0: sh zero,0xa(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x0000000a),(uint16_t)c->r[0]);
/* 00257ca4: lui v0,0x40 */ c->r[2]=sx(UINT32_C(0x00400000));
/* 00257ca8: addu v0,v0,a1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[5]);
/* 00257cac: lw v0,-0x5840(v0) */ c->r[2]=sx(word((uint32_t)c->r[2]+UINT32_C(0xffffa7c0)));
/* 00257cb0: jalr v0 */ c->r[31]=UINT64_C(0x00257cb8);/* delay 00257cb4 */ (void)0;{BattleCallbackNativeBoundary b=boundary(c,UINT32_C(0x00257cb0),UINT32_C(0xa000003c)|inherited_mask);nocturneBattleCallbackNativeSetStackPointer((uint32_t)c->r[29]);nocturneBattleCallbackNativeEntry(&b);nocturneBattleCallbackNativeSetStackPointer((uint32_t)c->r[29]);}
/* 00257cb8: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00257cbc: jr ra */ /* delay 00257cc0 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_00257cd0(BattleCallbackNativeValues *c){
/* 00257cd0: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 00257cd4: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00257cd8: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00257cdc: sd ra,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[31]);
/* 00257ce0: jal 0x00101ab0 */ c->r[31]=UINT64_C(0x00257ce8);/* delay 00257ce4 */ (void)0;nocturneBattleCallbackNativeSetStackPointer((uint32_t)c->r[29]);c->r[2]=dds3GetProcessData(c->r[4]);nocturneBattleCallbackNativeSetStackPointer((uint32_t)c->r[29]);
/* 00257ce8: move s0,v0 */ c->r[16]=c->r[2];
/* 00257cec: lw v0,0x4(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000004)));
/* 00257cf0: andi v0,v0,0x400 */ c->r[2]=c->r[2]&UINT64_C(0x400);
/* 00257cf4: beq v0,zero,0x00257d08 */ {int taken=c->r[2]==c->r[0];/* delay 00257cf8 */ (void)0;if(taken){goto L_00257d08;}}
/* 00257cfc: lw a0,0x0(s0) */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 00257d00: jal 0x0027fd18 */ c->r[31]=UINT64_C(0x00257d08);/* delay 00257d04 */ c->r[5]=c->r[0];nocturneBattleCallbackNativeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbPanelStockSelect(c->r[4],c->r[5]);nocturneBattleCallbackNativeSetStackPointer((uint32_t)c->r[29]);
L_00257d08:;
/* 00257d08: jal 0x00257c20 */ c->r[31]=UINT64_C(0x00257d10);/* delay 00257d0c */ c->r[17]=sx(UINT32_C(0x00000001));nocturneBattleCallbackNativeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetPrevActionSeq();nocturneBattleCallbackNativeSetStackPointer((uint32_t)c->r[29]);
/* 00257d10: lw a0,0x4(s0) */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000004)));
/* 00257d14: move a1,v0 */ c->r[5]=c->r[2];
/* 00257d18: andi v0,a0,0x2 */ c->r[2]=c->r[4]&UINT64_C(0x2);
/* 00257d1c: beql v0,zero,0x00257d28 */ {int taken=c->r[2]==c->r[0];if(taken){/* delay 00257d20 */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[16]+UINT32_C(0x00000008)));goto L_00257d28;}}
/* 00257d24: lb v0,0x9(s0) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[16]+UINT32_C(0x00000009)));
L_00257d28:;
/* 00257d28: addiu v1,v0,-0x7 */ c->r[3]=sx((uint32_t)c->r[2]+UINT32_C(0xfffffff9));
/* 00257d2c: sltiu v0,v1,0x8 */ c->r[2]=(c->r[3]<sx(UINT32_C(0x00000008)));
/* 00257d30: beql v0,zero,0x00257d7c */ {int taken=c->r[2]==c->r[0];if(taken){/* delay 00257d34 */ c->r[3]=c->r[4]&UINT64_C(0x40);goto L_00257d7c;}}
/* 00257d38: sll v0,v1,0x2 */ c->r[2]=sx((uint32_t)c->r[3]<<2u);
/* 00257d3c: lui v1,0x54 */ c->r[3]=sx(UINT32_C(0x00540000));
/* 00257d40: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 00257d44: lw v1,0x4100(v1) */ c->r[3]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00004100)));
/* 00257d48: jr v1 */ /* delay 00257d4c */ (void)0;switch(c->r[3]){case UINT64_C(0x00257d50):goto L_00257d50;case UINT64_C(0x00257d78):goto L_00257d78;default:abort();}
L_00257d50:;
/* 00257d50: sltiu v0,a1,0x13 */ c->r[2]=(c->r[5]<sx(UINT32_C(0x00000013)));
/* 00257d54: jal 0x002c2178 */ c->r[31]=UINT64_C(0x00257d5c);/* delay 00257d58 */ c->r[17]=(c->r[2]<sx(UINT32_C(0x00000001)));nocturneBattleCallbackNativeSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2MovieCheckAdpcmFlag();nocturneBattleCallbackNativeSetStackPointer((uint32_t)c->r[29]);
/* 00257d5c: beq v0,zero,0x00257d74 */ {int taken=c->r[2]==c->r[0];/* delay 00257d60 */ c->r[4]=sx(UINT32_C(0x00540000));if(taken){goto L_00257d74;}}
/* 00257d64: jal 0x002d4748 */ c->r[31]=UINT64_C(0x00257d6c);/* delay 00257d68 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x000040e8));{BattleCallbackNativeBoundary b=boundary(c,UINT32_C(0x00257d64),UINT32_C(0xa0030010));nocturneBattleCallbackNativeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleCallbackNativePrintf(&b);nocturneBattleCallbackNativeSetStackPointer((uint32_t)c->r[29]);}
/* 00257d6c: jal 0x002c2180 */ c->r[31]=UINT64_C(0x00257d74);/* delay 00257d70 */ (void)0;nocturneBattleCallbackNativeSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2MovieStopAdpcm();nocturneBattleCallbackNativeSetStackPointer((uint32_t)c->r[29]);
L_00257d74:;
/* 00257d74: lw a0,0x4(s0) */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000004)));
L_00257d78:;
/* 00257d78: andi v1,a0,0x40 */ c->r[3]=c->r[4]&UINT64_C(0x40);
L_00257d7c:;
/* 00257d7c: bne v1,zero,0x00257e18 */ {int taken=c->r[3]!=c->r[0];/* delay 00257d80 */ c->r[2]=c->r[0];if(taken){goto L_00257e18;}}
/* 00257d84: beq s1,zero,0x00257e14 */ {int taken=c->r[17]==c->r[0];/* delay 00257d88 */ c->r[2]=c->r[4]&UINT64_C(0x2);if(taken){goto L_00257e14;}}
/* 00257d8c: beq v0,zero,0x00257dc8 */ {int taken=c->r[2]==c->r[0];/* delay 00257d90 */ c->r[3]=sx(UINT32_C(0x00000016));if(taken){goto L_00257dc8;}}
/* 00257d94: lb a0,0x8(s0) */ c->r[4]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[16]+UINT32_C(0x00000008)));
/* 00257d98: beq a0,v1,0x00257e18 */ {int taken=c->r[4]==c->r[3];/* delay 00257d9c */ c->r[2]=sx(UINT32_C(0xffffffff));if(taken){goto L_00257e18;}}
/* 00257da0: lb a1,0x9(s0) */ c->r[5]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[16]+UINT32_C(0x00000009)));
/* 00257da4: jal 0x00257c80 */ c->r[31]=UINT64_C(0x00257dac);/* delay 00257da8 */ c->r[4]=c->r[16];body_00257c80(c,UINT32_C(0x00030000));
/* 00257dac: lw v1,0x4(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000004)));
/* 00257db0: li a0,-0x3 */ c->r[4]=sx(UINT32_C(0xfffffffd));
/* 00257db4: move v0,zero */ c->r[2]=c->r[0];
/* 00257db8: and v1,v1,a0 */ c->r[3]=c->r[3]&c->r[4];
/* 00257dbc: b 0x00257e18 */ /* delay 00257dc0 */ sw((uint32_t)c->r[16]+UINT32_C(0x00000004),(uint32_t)c->r[3]);goto L_00257e18;
L_00257dc8:;
/* 00257dc8: lb v1,0x8(s0) */ c->r[3]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[16]+UINT32_C(0x00000008)));
/* 00257dcc: sll v1,v1,0x3 */ c->r[3]=sx((uint32_t)c->r[3]<<3u);
/* 00257dd0: lui v0,0x40 */ c->r[2]=sx(UINT32_C(0x00400000));
/* 00257dd4: addu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[3]);
/* 00257dd8: lw v0,-0x583c(v0) */ c->r[2]=sx(word((uint32_t)c->r[2]+UINT32_C(0xffffa7c4)));
/* 00257ddc: jalr v0 */ c->r[31]=UINT64_C(0x00257de4);/* delay 00257de0 */ c->r[4]=c->r[16];{BattleCallbackNativeBoundary b=boundary(c,UINT32_C(0x00257ddc),UINT32_C(0xa003001c));nocturneBattleCallbackNativeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleCallbackNativeUpdate(&b);nocturneBattleCallbackNativeSetStackPointer((uint32_t)c->r[29]);}
/* 00257de4: beql v0,zero,0x00257dfc */ {int taken=c->r[2]==c->r[0];if(taken){/* delay 00257de8 */ c->r[3]=hword((uint32_t)c->r[16]+UINT32_C(0x0000000a));goto L_00257dfc;}}
/* 00257dec: lw v0,0x4(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000004)));
/* 00257df0: ori v0,v0,0x2 */ c->r[2]=c->r[2]|UINT64_C(0x2);
/* 00257df4: sw v0,0x4(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000004),(uint32_t)c->r[2]);
/* 00257df8: lhu v1,0xa(s0) */ c->r[3]=hword((uint32_t)c->r[16]+UINT32_C(0x0000000a));
L_00257dfc:;
/* 00257dfc: ori v0,zero,0xfffe */ c->r[2]=c->r[0]|UINT64_C(0xfffe);
/* 00257e00: sltu v0,v0,v1 */ c->r[2]=(c->r[2]<c->r[3]);
/* 00257e04: bne v0,zero,0x00257e18 */ {int taken=c->r[2]!=c->r[0];/* delay 00257e08 */ c->r[2]=c->r[0];if(taken){goto L_00257e18;}}
/* 00257e0c: addiu v0,v1,0x1 */ c->r[2]=sx((uint32_t)c->r[3]+UINT32_C(0x00000001));
/* 00257e10: sh v0,0xa(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x0000000a),(uint16_t)c->r[2]);
L_00257e14:;
/* 00257e14: move v0,zero */ c->r[2]=c->r[0];
L_00257e18:;
/* 00257e18: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00257e1c: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00257e20: ld ra,0x10(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00257e24: jr ra */ /* delay 00257e28 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

void ps2BattleCallbackNative_00257C80(uint64_t context,uint64_t raw_state){BattleCallbackNativeValues c=begin();c.r[4]=context;c.r[5]=raw_state;body_00257c80(&c,0);nocturneBattleCallbackNativeSetStackPointer((uint32_t)c.r[29]);}
uint64_t ps2BattleCallbackNative_00257CD0(uint64_t process){BattleCallbackNativeValues c=begin();c.r[4]=process;body_00257cd0(&c);nocturneBattleCallbackNativeSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
