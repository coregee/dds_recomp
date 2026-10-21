/* Existing38 EXP/item/process native variants; zero identity credit; fixed native-PC statements.
 * Actual128 upper halves survive every scalar write; external calls remain
 * explicitly unimplemented native bank/frame routes. No runtime decoder,
 * result provider, source register-zero fill or per-call upper-word trace. */
#include "battle_reward_phase_dependencies.h"

#include "ee_fpu.h"
#include "script_compare.h"
#include <stdlib.h>
#include <string.h>
uint32_t *nocturneEffectHostFpr(void);
uint64_t nocturneEffectHostLo(void);
uint64_t nocturneEffectHostHi(void);
void nocturneEffectHostSetHilo(uint64_t lo,uint64_t hi);
static uint8_t *at(uint32_t a){return nocturneResolveBattleRewardPhaseNativeAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneBattleRewardPhaseNativeCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){
 uint32_t q[4];if(!r)return;nocturneBattleRewardPhaseNativeCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);
 nocturneBattleRewardPhaseNativeCpuWrite(r,q);if(r==29u)nocturneBattleRewardPhaseNativeSetStackPointer(q[0]);
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



void nocturneBattleActionFormulaSecondaryWrite(uint64_t lo,uint64_t hi);
static void sb(uint32_t a,uint8_t v){*at(a)=v;}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}

static void nativeMultiply(unsigned rd,uint32_t a,uint32_t b,int isSigned,int secondary){
 uint64_t p=isSigned?(uint64_t)((int64_t)(int32_t)a*(int64_t)(int32_t)b):(uint64_t)a*b;
 if(secondary)nocturneBattleActionFormulaSecondaryWrite(sx((uint32_t)p),sx((uint32_t)(p>>32)));
 else nocturneEffectHostSetHilo(sx((uint32_t)p),sx((uint32_t)(p>>32)));
 if(rd)set(rd,sx((uint32_t)p));
}







#include "ee_fpu_sqrt.h"
#include "ee_vu_rotation.h"





static void loadPartial(unsigned r,uint32_t a,int left){uint8_t d[8],s[8];uint64_t v=cpu(r);memcpy(d,&v,8);memcpy(s,at(a&~7u),8);unsigned o=a&7u;if(left){for(unsigned i=0;i<=o;i++)d[7u-o+i]=s[i];}else{for(unsigned i=o;i<8;i++)d[i-o]=s[i];}memcpy(&v,d,8);set(r,v);}
static void storePartial(uint32_t a,unsigned r,int left){uint8_t s[8];uint64_t v=cpu(r);memcpy(s,&v,8);uint8_t *d=at(a&~7u);unsigned o=a&7u;if(left){for(unsigned i=0;i<=o;i++)d[i]=s[7u-o+i];}else{for(unsigned i=o;i<8;i++)d[i]=s[i-o];}}


static void body_001005e8(void);
static void body_00100760(void);
static void body_001009a0(void);
static void body_00100d70(void);
static void body_00100e08(void);
static void body_001015b0(void);
static void body_00101738(void);
static void body_00101af8(void);
static void body_00101b80(void);
static void body_001e0ed0(void);
static void body_001e0f10(void);
static void body_001fef20(void);
static void body_002138c0(void);
static void body_0021f838(void);
static void body_0021f898(void);
static void body_002221d0(void);
static void body_002224d8(void);
static void body_00222550(void);
static void body_00223628(void);
static void body_00223668(void);
static void body_00223728(void);
static void body_00223928(void);
static void body_00232880(void);
static void body_002328c8(void);
static void body_00242ae8(void);
static void body_00243c28(void);
static void body_00243d28(void);
static void body_00244238(void);
static void body_002442e0(void);
static void body_002452b8(void);
static void body_002452c8(void);
static void body_00269318(void);
static void body_0026a840(void);
static void body_0026a870(void);
static void body_002d1b88(void);
static void body_002d1c40(void);
static void body_002d34a0(void);
static void body_002d3578(void);
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
static void body_001009a0(void){
uint64_t incoming=cpu(31);
/* 001009a0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001009a4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001009a8: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001009ac: jal 0x001005e8 */ set(31,UINT64_C(0x001009b4));/* delay 001009b0 */ set(16,cpu(4));body_001005e8();
/* 001009b4: lw v0,0x1c(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 001009b8: li v1,-0x10 */ set(3,sx(UINT32_C(0xfffffff0)));
/* 001009bc: move a0,s0 */ set(4,cpu(16));
/* 001009c0: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 001009c4: ori v0,v0,0x2 */ set(2,cpu(2)|UINT32_C(0x00000002));
/* 001009c8: jal 0x00100760 */ set(31,UINT64_C(0x001009d0));/* delay 001009cc */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));body_00100760();
/* 001009d0: sw zero,0x24(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(0));
/* 001009d4: sw zero,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(0));
/* 001009d8: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001009dc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001009e0: jr ra */ {uint64_t target=cpu(31);/* delay 001009e4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
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
/* 00100dbc: jal 0x002d4748 */ set(31,UINT64_C(0x00100dc4));/* delay 00100dc0 */ set(5,cpu(17));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002d4748),UINT32_C(0x00100dbc));
/* 00100dc4: lw v0,0x34(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000034)));
/* 00100dc8: beql v0,zero,0x00100ddc */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00100dcc */ lw(2,ea(17,(int32_t)UINT32_C(0x0000001c)));goto L_00100ddc;}}
/* 00100dd0: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x00100dd8));/* delay 00100dd4 */ set(4,cpu(17));nocturneBattleRewardPhaseNativeIndirect(target,UINT32_C(0x00100dd0));}
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
/* 00100e00: j 0x002a8bd8 */ /* delay 00100e04 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002a8bd8),UINT32_C(0x00100e00));return;
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
/* 001015f4: jal 0x002a8af8 */ set(31,UINT64_C(0x001015fc));/* delay 001015f8 */ set(23,cpu(10));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002a8af8),UINT32_C(0x001015f4));
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
/* 001016b4: jal 0x001009a0 */ set(31,UINT64_C(0x001016bc));/* delay 001016b8 */ set(4,cpu(16));body_001009a0();
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
static void body_00101af8(void){
uint64_t incoming=cpu(31);
/* 00101af8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00101afc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00101b00: move s0,a1 */ set(16,cpu(5));
/* 00101b04: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00101b08: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00101b0c: lw v0,0x44(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000044)));
/* 00101b10: beq v0,zero,0x00101b20 */ {int taken=(cpu(2)==cpu(0));/* delay 00101b14 */ set(17,cpu(4));if(taken){goto L_00101b20;}}
/* 00101b18: jal 0x00101b80 */ set(31,UINT64_C(0x00101b20));/* delay 00101b1c */ set(4,cpu(16));body_00101b80();
L_00101b20:;
/* 00101b20: lw v0,0x48(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000048)));
/* 00101b24: beq v0,zero,0x00101b60 */ {int taken=(cpu(2)==cpu(0));/* delay 00101b28 */ set(4,cpu(2));if(taken){goto L_00101b60;}}
/* 00101b2c: lw v1,0x4c(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x0000004c)));
/* 00101b30: beql v1,zero,0x00101b64 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00101b34 */ sw(ea(4,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(16));goto L_00101b64;}}
L_00101b38:;
/* 00101b38: move a0,v1 */ set(4,cpu(3));
/* 00101b3c: lw v0,0x4c(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000004c)));
/* 00101b40: nop  */ 
/* 00101b44: nop  */ 
/* 00101b48: nop  */ 
/* 00101b4c: bne v0,zero,0x00101b38 */ {int taken=(cpu(2)!=cpu(0));/* delay 00101b50 */ set(3,cpu(2));if(taken){goto L_00101b38;}}
/* 00101b54: b 0x00101b64 */ /* delay 00101b58 */ sw(ea(4,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(16));goto L_00101b64;
L_00101b60:;
/* 00101b60: sw s0,0x48(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(16));
L_00101b64:;
/* 00101b64: sw s1,0x44(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(17));
/* 00101b68: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00101b6c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00101b70: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00101b74: jr ra */ {uint64_t target=cpu(31);/* delay 00101b78 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
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
static void body_001e0ed0(void){
uint64_t incoming=cpu(31);
/* 001e0ed0: slti v1,a0,0x0 */ set(3,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 001e0ed4: addiu a3,a0,0x1f */ set(7,sx((uint32_t)cpu(4)+UINT32_C(0x0000001f)));
/* 001e0ed8: move v0,a0 */ set(2,cpu(4));
/* 001e0edc: lw a2,-0x5750(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001e0ee0: movn v0,a3,v1 */ if(cpu(3)!=0){set(2,cpu(7));}
/* 001e0ee4: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 001e0ee8: sra v0,v0,0x5 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>5)));
/* 001e0eec: sllv a1,a1,a0 */ set(5,sx((uint32_t)((uint32_t)cpu(5)<<((uint32_t)cpu(4)&31u))));
/* 001e0ef0: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001e0ef4: addiu v0,v0,0x840 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000840)));
/* 001e0ef8: addu a2,a2,v0 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(2)));
/* 001e0efc: lw v1,0x0(a2) */ lw(3,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 001e0f00: or v1,v1,a1 */ set(3,cpu(3)|cpu(5));
/* 001e0f04: jr ra */ {uint64_t target=cpu(31);/* delay 001e0f08 */ sw(ea(6,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));checkReturn(target,incoming);return;}
}
static void body_001e0f10(void){
uint64_t incoming=cpu(31);
/* 001e0f10: slti v0,a0,0x0 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 001e0f14: addiu a3,a0,0x1f */ set(7,sx((uint32_t)cpu(4)+UINT32_C(0x0000001f)));
/* 001e0f18: move v1,a0 */ set(3,cpu(4));
/* 001e0f1c: lw a2,-0x5750(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001e0f20: movn v1,a3,v0 */ if(cpu(2)!=0){set(3,cpu(7));}
/* 001e0f24: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 001e0f28: sra v1,v1,0x5 */ set(3,sx((uint32_t)((int32_t)cpu(3)>>5)));
/* 001e0f2c: sllv a1,a1,a0 */ set(5,sx((uint32_t)((uint32_t)cpu(5)<<((uint32_t)cpu(4)&31u))));
/* 001e0f30: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 001e0f34: nor a1,zero,a1 */ set(5,~(cpu(0)|cpu(5)));
/* 001e0f38: addiu v1,v1,0x840 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000840)));
/* 001e0f3c: addu a2,a2,v1 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(3)));
/* 001e0f40: lw v0,0x0(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 001e0f44: and v0,v0,a1 */ set(2,cpu(2)&cpu(5));
/* 001e0f48: jr ra */ {uint64_t target=cpu(31);/* delay 001e0f4c */ sw(ea(6,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_001fef20(void){
uint64_t incoming=cpu(31);
/* 001fef20: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001fef24: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001fef28: move s0,a0 */ set(16,cpu(4));
/* 001fef2c: or v0,a1,s0 */ set(2,cpu(5)|cpu(16));
/* 001fef30: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001fef34: andi v0,v0,0x7 */ set(2,cpu(2)&UINT32_C(0x00000007));
/* 001fef38: beq v0,zero,0x001fefa0 */ {int taken=(cpu(2)==cpu(0));/* delay 001fef3c */ set(3,cpu(16));if(taken){goto L_001fefa0;}}
/* 001fef40: addiu v0,a1,0xe0 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x000000e0)));
L_001fef44:;
/* 001fef44: ldl a0,0x7(a1) */ loadPartial(4,ea(5,(int32_t)UINT32_C(0x00000007)),1);
/* 001fef48: ldr a0,0x0(a1) */ loadPartial(4,ea(5,(int32_t)UINT32_C(0x00000000)),0);
/* 001fef4c: ldl a2,0xf(a1) */ loadPartial(6,ea(5,(int32_t)UINT32_C(0x0000000f)),1);
/* 001fef50: ldr a2,0x8(a1) */ loadPartial(6,ea(5,(int32_t)UINT32_C(0x00000008)),0);
/* 001fef54: ldl a3,0x17(a1) */ loadPartial(7,ea(5,(int32_t)UINT32_C(0x00000017)),1);
/* 001fef58: ldr a3,0x10(a1) */ loadPartial(7,ea(5,(int32_t)UINT32_C(0x00000010)),0);
/* 001fef5c: ldl t0,0x1f(a1) */ loadPartial(8,ea(5,(int32_t)UINT32_C(0x0000001f)),1);
/* 001fef60: ldr t0,0x18(a1) */ loadPartial(8,ea(5,(int32_t)UINT32_C(0x00000018)),0);
/* 001fef64: sdl a0,0x7(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000007)),4,1);
/* 001fef68: sdr a0,0x0(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000000)),4,0);
/* 001fef6c: sdl a2,0xf(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000000f)),6,1);
/* 001fef70: sdr a2,0x8(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000008)),6,0);
/* 001fef74: sdl a3,0x17(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000017)),7,1);
/* 001fef78: sdr a3,0x10(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000010)),7,0);
/* 001fef7c: sdl t0,0x1f(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000001f)),8,1);
/* 001fef80: sdr t0,0x18(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000018)),8,0);
/* 001fef84: addiu a1,a1,0x20 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));
/* 001fef88: nop  */ 
/* 001fef8c: nop  */ 
/* 001fef90: bne a1,v0,0x001fef44 */ {int taken=(cpu(5)!=cpu(2));/* delay 001fef94 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));if(taken){goto L_001fef44;}}
/* 001fef98: b 0x001fefd8 */ /* delay 001fef9c */ goto L_001fefd8;
L_001fefa0:;
/* 001fefa0: addiu v0,a1,0xe0 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x000000e0)));
L_001fefa4:;
/* 001fefa4: ld a0,0x0(a1) */ restore(4,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 001fefa8: ld a2,0x8(a1) */ restore(6,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 001fefac: ld a3,0x10(a1) */ restore(7,ea(5,(int32_t)UINT32_C(0x00000010)));
/* 001fefb0: ld t0,0x18(a1) */ restore(8,ea(5,(int32_t)UINT32_C(0x00000018)));
/* 001fefb4: sd a0,0x0(v1) */ save(4,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001fefb8: sd a2,0x8(v1) */ save(6,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 001fefbc: sd a3,0x10(v1) */ save(7,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 001fefc0: sd t0,0x18(v1) */ save(8,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 001fefc4: addiu a1,a1,0x20 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));
/* 001fefc8: nop  */ 
/* 001fefcc: nop  */ 
/* 001fefd0: bne a1,v0,0x001fefa4 */ {int taken=(cpu(5)!=cpu(2));/* delay 001fefd4 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));if(taken){goto L_001fefa4;}}
L_001fefd8:;
/* 001fefd8: ldl v0,0x7(a1) */ loadPartial(2,ea(5,(int32_t)UINT32_C(0x00000007)),1);
/* 001fefdc: ldr v0,0x0(a1) */ loadPartial(2,ea(5,(int32_t)UINT32_C(0x00000000)),0);
/* 001fefe0: lw a0,0x8(a1) */ lw(4,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 001fefe4: sdl v0,0x7(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000007)),2,1);
/* 001fefe8: sdr v0,0x0(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000000)),2,0);
/* 001fefec: sw a0,0x8(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(4));
/* 001feff0: jal 0x00243c28 */ set(31,UINT64_C(0x001feff8));/* delay 001feff4 */ set(4,cpu(16));body_00243c28();
/* 001feff8: move a0,s0 */ set(4,cpu(16));
/* 001feffc: jal 0x00243d28 */ set(31,UINT64_C(0x001ff004));/* delay 001ff000 */ sh(ea(16,(int32_t)UINT32_C(0x00000008)),(uint16_t)cpu(2));body_00243d28();
/* 001ff004: lhu a0,0x8(s0) */ set(4,half(ea(16,(int32_t)UINT32_C(0x00000008))));
/* 001ff008: lhu v1,0x6(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000006))));
/* 001ff00c: sltu v1,a0,v1 */ set(3,cpu(4)<cpu(3));
/* 001ff010: beq v1,zero,0x001ff01c */ {int taken=(cpu(3)==cpu(0));/* delay 001ff014 */ sh(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(2));if(taken){goto L_001ff01c;}}
/* 001ff018: sh a0,0x6(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000006)),(uint16_t)cpu(4));
L_001ff01c:;
/* 001ff01c: lhu v1,0xc(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x0000000c))));
/* 001ff020: lhu v0,0xa(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x0000000a))));
/* 001ff024: sltu v0,v1,v0 */ set(2,cpu(3)<cpu(2));
/* 001ff028: bnel v0,zero,0x001ff030 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001ff02c */ sh(ea(16,(int32_t)UINT32_C(0x0000000a)),(uint16_t)cpu(3));goto L_001ff030;}}
L_001ff030:;
/* 001ff030: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 001ff034: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001ff038: ori v0,v0,0x1 */ set(2,cpu(2)|UINT32_C(0x00000001));
/* 001ff03c: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 001ff040: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001ff044: jr ra */ {uint64_t target=cpu(31);/* delay 001ff048 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002138c0(void){
uint64_t incoming=cpu(31);
/* 002138c0: andi a0,a0,0xffff */ set(4,cpu(4)&UINT32_C(0x0000ffff));
/* 002138c4: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002138c8: ori v0,zero,0xffc0 */ set(2,cpu(0)|UINT32_C(0x0000ffc0));
/* 002138cc: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002138d0: addu a0,a0,sp */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(29)));
/* 002138d4: andi v0,v0,0xffff */ set(2,cpu(2)&UINT32_C(0x0000ffff));
/* 002138d8: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 002138dc: sltiu v0,v0,0x19 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000019));
/* 002138e0: addiu t0,v1,-0x2918 */ set(8,sx((uint32_t)cpu(3)+UINT32_C(0xffffd6e8)));
/* 002138e4: ldl a1,0x7(t0) */ loadPartial(5,ea(8,(int32_t)UINT32_C(0x00000007)),1);
/* 002138e8: ldr a1,0x0(t0) */ loadPartial(5,ea(8,(int32_t)UINT32_C(0x00000000)),0);
/* 002138ec: ldl a2,0xf(t0) */ loadPartial(6,ea(8,(int32_t)UINT32_C(0x0000000f)),1);
/* 002138f0: ldr a2,0x8(t0) */ loadPartial(6,ea(8,(int32_t)UINT32_C(0x00000008)),0);
/* 002138f4: ldl a3,0x17(t0) */ loadPartial(7,ea(8,(int32_t)UINT32_C(0x00000017)),1);
/* 002138f8: ldr a3,0x10(t0) */ loadPartial(7,ea(8,(int32_t)UINT32_C(0x00000010)),0);
/* 002138fc: sdl a1,0x7(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000007)),5,1);
/* 00213900: sdr a1,0x0(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000000)),5,0);
/* 00213904: sdl a2,0xf(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x0000000f)),6,1);
/* 00213908: sdr a2,0x8(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000008)),6,0);
/* 0021390c: sdl a3,0x17(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000017)),7,1);
/* 00213910: sdr a3,0x10(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000010)),7,0);
/* 00213914: lb a1,0x18(t0) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(8,(int32_t)UINT32_C(0x00000018))));
/* 00213918: sb a1,0x18(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000018)),(uint8_t)cpu(5));
/* 0021391c: beq v0,zero,0x00213928 */ {int taken=(cpu(2)==cpu(0));/* delay 00213920 */ set(3,cpu(0));if(taken){goto L_00213928;}}
/* 00213924: lb v1,-0x40(a0) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0xffffffc0))));
L_00213928:;
/* 00213928: move v0,v1 */ set(2,cpu(3));
/* 0021392c: jr ra */ {uint64_t target=cpu(31);/* delay 00213930 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_0021f838(void){
uint64_t incoming=cpu(31);
/* 0021f838: andi a0,a0,0xff */ set(4,cpu(4)&UINT32_C(0x000000ff));
/* 0021f83c: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0021f840: sll v0,a0,0x4 */ set(2,sx((uint32_t)cpu(4)<<4));
/* 0021f844: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0021f848: subu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));
/* 0021f84c: lw s0,-0x5750(gp) */ lw(16,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0021f850: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0021f854: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0021f858: subu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));
/* 0021f85c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0021f860: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 0021f864: addiu s0,s0,0xa54 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000a54)));
/* 0021f868: lw v0,0x10(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 0021f86c: move a0,s0 */ set(4,cpu(16));
/* 0021f870: jal 0x00223928 */ set(31,UINT64_C(0x0021f878));/* delay 0021f874 */ set(5,sx((uint32_t)cpu(5)-(uint32_t)cpu(2)));body_00223928();
/* 0021f878: lbu v1,0x14(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000014))));
/* 0021f87c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0021f880: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0021f884: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0021f888: andi v0,v1,0xff */ set(2,cpu(3)&UINT32_C(0x000000ff));
/* 0021f88c: jr ra */ {uint64_t target=cpu(31);/* delay 0021f890 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_0021f898(void){
uint64_t incoming=cpu(31);
/* 0021f898: andi a0,a0,0xff */ set(4,cpu(4)&UINT32_C(0x000000ff));
/* 0021f89c: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0021f8a0: sll v0,a0,0x4 */ set(2,sx((uint32_t)cpu(4)<<4));
/* 0021f8a4: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0021f8a8: subu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));
/* 0021f8ac: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0021f8b0: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0021f8b4: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0021f8b8: subu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));
/* 0021f8bc: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0021f8c0: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0021f8c4: addiu a0,v1,0xa54 */ set(4,sx((uint32_t)cpu(3)+UINT32_C(0x00000a54)));
/* 0021f8c8: j 0x00223668 */ /* delay 0021f8cc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_00223668();return;
}
static void body_002221d0(void){
uint64_t incoming=cpu(31);
/* 002221d0: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 002221d4: andi a0,a0,0xff */ set(4,cpu(4)&UINT32_C(0x000000ff));
/* 002221d8: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 002221dc: lbu v0,0x1d3b(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00001d3b))));
/* 002221e0: jr ra */ {uint64_t target=cpu(31);/* delay 002221e4 */ set(2,cpu(2)&UINT32_C(0x0000000f));checkReturn(target,incoming);return;}
}
static void body_002224d8(void){
uint64_t incoming=cpu(31);
/* 002224d8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002224dc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002224e0: sll s0,a0,0x18 */ set(16,sx((uint32_t)cpu(4)<<24));
/* 002224e4: sra s0,s0,0x18 */ set(16,sx((uint32_t)((int32_t)cpu(16)>>24)));
/* 002224e8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002224ec: andi a0,s0,0xff */ set(4,cpu(16)&UINT32_C(0x000000ff));
/* 002224f0: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002224f4: jal 0x002221d0 */ set(31,UINT64_C(0x002224fc));/* delay 002224f8 */ set(17,cpu(5)&UINT32_C(0x0000ffff));body_002221d0();
/* 002224fc: sll v1,s0,0x1 */ set(3,sx((uint32_t)cpu(16)<<1));
/* 00222500: lw a0,-0x5750(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 00222504: addu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));
/* 00222508: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0022250c: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 00222510: addu s0,s0,a0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(4)));
/* 00222514: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00222518: addiu s0,s0,0x1d3b */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00001d3b)));
/* 0022251c: sll v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)<<1));
/* 00222520: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 00222524: lui at,0x1 */ set(1,sx(UINT32_C(0x00010000)));
/* 00222528: addu at,at,v1 */ set(1,sx((uint32_t)cpu(1)+(uint32_t)cpu(3)));
/* 0022252c: sh s1,0x1ac0(at) */ sh(ea(1,(int32_t)UINT32_C(0x00001ac0)),(uint16_t)cpu(17));
/* 00222530: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00222534: lbu v0,0x0(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 00222538: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0022253c: sb v0,0x0(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 00222540: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00222544: jr ra */ {uint64_t target=cpu(31);/* delay 00222548 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00222550(void){
uint64_t incoming=cpu(31);
/* 00222550: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00222554: andi a0,a0,0xff */ set(4,cpu(4)&UINT32_C(0x000000ff));
/* 00222558: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0022255c: move s1,a1 */ set(17,cpu(5));
/* 00222560: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00222564: move v0,zero */ set(2,cpu(0));
/* 00222568: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0022256c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00222570: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00222574: beq a0,zero,0x002225f0 */ {int taken=(cpu(4)==cpu(0));/* delay 00222578 */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));if(taken){goto L_002225f0;}}
/* 0022257c: sll v0,a0,0x5 */ set(2,sx((uint32_t)cpu(4)<<5));
/* 00222580: addiu s4,s1,0xa */ set(20,sx((uint32_t)cpu(17)+UINT32_C(0x0000000a)));
/* 00222584: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 00222588: sll s3,a0,0x18 */ set(19,sx((uint32_t)cpu(4)<<24));
/* 0022258c: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 00222590: li s2,0x7 */ set(18,sx(UINT32_C(0x00000007)));
/* 00222594: lui s0,0x34 */ set(16,sx(UINT32_C(0x00340000)));
/* 00222598: addiu s0,s0,-0x61e6 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffff9e1a)));
/* 0022259c: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
L_002225a0:;
/* 002225a0: lhu a2,0x2(s0) */ set(6,half(ea(16,(int32_t)UINT32_C(0x00000002))));
/* 002225a4: beql a2,zero,0x002225e4 */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 002225a8 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0xffffffff)));goto L_002225e4;}}
/* 002225ac: lbu v0,0x0(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 002225b0: bnel v0,zero,0x002225e4 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002225b4 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0xffffffff)));goto L_002225e4;}}
/* 002225b8: lhu v1,0x38(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x00000038))));
/* 002225bc: move a1,a2 */ set(5,cpu(6));
/* 002225c0: sra a0,s3,0x18 */ set(4,sx((uint32_t)((int32_t)cpu(19)>>24)));
/* 002225c4: move v0,v1 */ set(2,cpu(3));
/* 002225c8: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002225cc: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 002225d0: sh v1,0x38(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000038)),(uint16_t)cpu(3));
/* 002225d4: addu v0,v0,s4 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(20)));
/* 002225d8: jal 0x002224d8 */ set(31,UINT64_C(0x002225e0));/* delay 002225dc */ sh(ea(2,(int32_t)UINT32_C(0x00000030)),(uint16_t)cpu(6));body_002224d8();
/* 002225e0: addiu s2,s2,-0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0xffffffff)));
L_002225e4:;
/* 002225e4: bgez s2,0x002225a0 */ {int taken=((int64_t)cpu(18)>=0);/* delay 002225e8 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000004)));if(taken){goto L_002225a0;}}
/* 002225ec: lb v0,0x38(s1) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x00000038))));
L_002225f0:;
/* 002225f0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002225f4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002225f8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002225fc: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00222600: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00222604: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00222608: jr ra */ {uint64_t target=cpu(31);/* delay 0022260c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_00223628(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 00223628: mult a0,a0 */ nativeMultiply(0,(uint32_t)cpu(4),(uint32_t)cpu(4),1,0);
/* 0022362c: lwc1 f1,-0x5d3c(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffffa2c4)));
/* 00223630: lui at,0xc0a0 */ set(1,sx(UINT32_C(0xc0a00000)));
/* 00223634: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 00223638: mflo v0 */ set(2,nocturneEffectHostLo());
/* 0022363c: mult v0,a0 */ nativeMultiply(0,(uint32_t)cpu(2),(uint32_t)cpu(4),1,0);
/* 00223640: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00223644: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 00223648: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0022364c: mul.S f0,f0,f1 */ f[0]=EE_FPU_MUL_S(f[0],f[1]);
/* 00223650: add.S f0,f0,f2 */ f[0]=EE_FPU_ADD_S(f[0],f[2]);
/* 00223654: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 00223658: mfc1 v0,f1 */ set(2,sx(f[1]));
/* 0022365c: slti v1,v0,0x0 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 00223660: jr ra */ {uint64_t target=cpu(31);/* delay 00223664 */ if(cpu(3)!=0){set(2,cpu(0));}checkReturn(target,incoming);return;}
}
static void body_00223668(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 00223668: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0022366c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00223670: move s1,a0 */ set(17,cpu(4));
/* 00223674: move a0,a1 */ set(4,cpu(5));
/* 00223678: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0022367c: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00223680: jal 0x00223628 */ set(31,UINT64_C(0x00223688));/* delay 00223684 */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[20]);body_00223628();
/* 00223688: lw v1,0x0(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0022368c: andi v1,v1,0x4 */ set(3,cpu(3)&UINT32_C(0x00000004));
/* 00223690: bne v1,zero,0x00223710 */ {int taken=(cpu(3)!=cpu(0));/* delay 00223694 */ set(4,cpu(2));if(taken){goto L_00223710;}}
/* 00223698: lhu v1,0x4(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x00000004))));
/* 0022369c: mtc1 a0,f2 */ f[2]=(uint32_t)cpu(4);
/* 002236a0: cvt.s.W f2,f2 */ f[2]=EE_FPU_CVT_S_W(f[2]);
/* 002236a4: lwc1 f0,-0x5d38(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffa2c8)));
/* 002236a8: sll v0,v1,0x4 */ set(2,sx((uint32_t)cpu(3)<<4));
/* 002236ac: lwc1 f20,-0x5d34(gp) */ f[20]=word(ea(28,(int32_t)UINT32_C(0xffffa2cc)));
/* 002236b0: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 002236b4: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002236b8: lui a0,0x35 */ set(4,sx(UINT32_C(0x00350000)));
/* 002236bc: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 002236c0: lbu a0,-0x683b(a0) */ set(4,byte(ea(4,(int32_t)UINT32_C(0xffff97c5))));
/* 002236c4: mtc1 a0,f1 */ f[1]=(uint32_t)cpu(4);
/* 002236c8: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 002236cc: mul.S f1,f1,f0 */ f[1]=EE_FPU_MUL_S(f[1],f[0]);
/* 002236d0: sub.S f20,f20,f1 */ f[20]=EE_FPU_SUB_S(f[20],f[1]);
/* 002236d4: mul.S f2,f2,f20 */ f[2]=EE_FPU_MUL_S(f[2],f[20]);
/* 002236d8: cvt.w.S f0,f2 */ f[0]=EE_FPU_CVT_W_S(f[2]);
/* 002236dc: mfc1 s0,f0 */ set(16,sx(f[0]));
/* 002236e0: jal 0x00223628 */ set(31,UINT64_C(0x002236e8));/* delay 002236e4 */ body_00223628();
/* 002236e8: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 002236ec: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 002236f0: lw v0,0xd8(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x000000d8)));
/* 002236f4: mtc1 s0,f0 */ f[0]=(uint32_t)cpu(16);
/* 002236f8: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 002236fc: mul.S f1,f1,f20 */ f[1]=EE_FPU_MUL_S(f[1],f[20]);
/* 00223700: sub.S f0,f0,f1 */ f[0]=EE_FPU_SUB_S(f[0],f[1]);
/* 00223704: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 00223708: mfc1 s0,f1 */ set(16,sx(f[1]));
/* 0022370c: addu v0,s0,v0 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
L_00223710:;
/* 00223710: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00223714: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00223718: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0022371c: lwc1 f20,0x18(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00223720: jr ra */ {uint64_t target=cpu(31);/* delay 00223724 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00223728(void){
uint64_t incoming=cpu(31);
/* 00223728: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0022372c: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00223730: lhu a1,0x14(a0) */ set(5,half(ea(4,(int32_t)UINT32_C(0x00000014))));
/* 00223734: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00223738: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0022373c: j 0x00223668 */ /* delay 00223740 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_00223668();return;
}
static void body_00223928(void){
uint64_t incoming=cpu(31);
/* 00223928: addiu sp,sp,-0x110 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffef0)));
/* 0022392c: move v0,a0 */ set(2,cpu(4));
/* 00223930: sd s0,0xf0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x000000f0)));
/* 00223934: move s0,a1 */ set(16,cpu(5));
/* 00223938: move a0,sp */ set(4,cpu(29));
/* 0022393c: move a1,v0 */ set(5,cpu(2));
/* 00223940: sd s1,0xf8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x000000f8)));
/* 00223944: sd ra,0x100(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000100)));
/* 00223948: jal 0x001fef20 */ set(31,UINT64_C(0x00223950));/* delay 0022394c */ set(17,cpu(0));body_001fef20();
/* 00223950: lw v0,0x10(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00223954: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 00223958: b 0x00223964 */ /* delay 0022395c */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));goto L_00223964;
L_00223960:;
/* 00223960: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
L_00223964:;
/* 00223964: jal 0x00223728 */ set(31,UINT64_C(0x0022396c));/* delay 00223968 */ set(4,cpu(29));body_00223728();
/* 0022396c: lw v1,0x10(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00223970: sltu v1,v1,v0 */ set(3,cpu(3)<cpu(2));
/* 00223974: bne v1,zero,0x00223998 */ {int taken=(cpu(3)!=cpu(0));/* delay 00223978 */ set(2,cpu(17));if(taken){goto L_00223998;}}
/* 0022397c: lhu v0,0x14(sp) */ set(2,half(ea(29,(int32_t)UINT32_C(0x00000014))));
/* 00223980: move v1,v0 */ set(3,cpu(2));
/* 00223984: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 00223988: sltiu v1,v1,0xff */ set(3,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x000000ff));
/* 0022398c: bne v1,zero,0x00223960 */ {int taken=(cpu(3)!=cpu(0));/* delay 00223990 */ sh(ea(29,(int32_t)UINT32_C(0x00000014)),(uint16_t)cpu(2));if(taken){goto L_00223960;}}
/* 00223994: move v0,s1 */ set(2,cpu(17));
L_00223998:;
/* 00223998: ld s0,0xf0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x000000f0)));
/* 0022399c: ld s1,0xf8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x000000f8)));
/* 002239a0: ld ra,0x100(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000100)));
/* 002239a4: jr ra */ {uint64_t target=cpu(31);/* delay 002239a8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000110)));checkReturn(target,incoming);return;}
}
static void body_00232880(void){
uint64_t incoming=cpu(31);
/* 00232880: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00232884: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00232888: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0023288c: li s0,0x1 */ set(16,sx(UINT32_C(0x00000001)));
/* 00232890: sll a0,s0,0x18 */ set(4,sx((uint32_t)cpu(16)<<24));
/* 00232894: nop  */ 
L_00232898:;
/* 00232898: addiu s0,s0,0x1 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));
/* 0023289c: jal 0x002328c8 */ set(31,UINT64_C(0x002328a4));/* delay 002328a0 */ set(4,sx((uint32_t)((int32_t)cpu(4)>>24)));body_002328c8();
/* 002328a4: beq v0,zero,0x002328b8 */ {int taken=(cpu(2)==cpu(0));/* delay 002328a8 */ set(3,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000019));if(taken){goto L_002328b8;}}
/* 002328ac: bnel v1,zero,0x00232898 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 002328b0 */ set(4,sx((uint32_t)cpu(16)<<24));goto L_00232898;}}
/* 002328b4: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_002328b8:;
/* 002328b8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002328bc: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002328c0: jr ra */ {uint64_t target=cpu(31);/* delay 002328c4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002328c8(void){
uint64_t incoming=cpu(31);
/* 002328c8: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 002328cc: sll a0,a0,0x18 */ set(4,sx((uint32_t)cpu(4)<<24));
/* 002328d0: sra a0,a0,0x18 */ set(4,sx((uint32_t)((int32_t)cpu(4)>>24)));
/* 002328d4: lbu v0,0x1d7b(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00001d7b))));
/* 002328d8: beq v0,zero,0x00232914 */ {int taken=(cpu(2)==cpu(0));/* delay 002328dc */ set(6,cpu(0));if(taken){goto L_00232914;}}
/* 002328e0: move a3,v0 */ set(7,cpu(2));
/* 002328e4: addiu a1,v1,0x1cfb */ set(5,sx((uint32_t)cpu(3)+UINT32_C(0x00001cfb)));
/* 002328e8: lbu v1,0x0(a1) */ set(3,byte(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 002328ec: nop  */ 
L_002328f0:;
/* 002328f0: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 002328f4: beq v1,a0,0x00232918 */ {int taken=(cpu(3)==cpu(4));/* delay 002328f8 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00232918;}}
/* 002328fc: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 00232900: slt v0,a2,a3 */ set(2,(int64_t)cpu(6)<(int64_t)cpu(7));
/* 00232904: nop  */ 
/* 00232908: nop  */ 
/* 0023290c: bnel v0,zero,0x002328f0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00232910 */ set(3,byte(ea(5,(int32_t)UINT32_C(0x00000000))));goto L_002328f0;}}
L_00232914:;
/* 00232914: move v0,zero */ set(2,cpu(0));
L_00232918:;
/* 00232918: jr ra */ {uint64_t target=cpu(31);/* delay 0023291c */ checkReturn(target,incoming);return;}
}
static void body_00242ae8(void){
uint64_t incoming=cpu(31);
/* 00242ae8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00242aec: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00242af0: move s0,a0 */ set(16,cpu(4));
/* 00242af4: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00242af8: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 00242afc: andi v0,v0,0x4 */ set(2,cpu(2)&UINT32_C(0x00000004));
/* 00242b00: jal 0x00243ee0 */ set(31,UINT64_C(0x00242b08));/* delay 00242b04 */ set(5,sx(UINT32_C(0x00000002)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00243ee0),UINT32_C(0x00242b00));
/* 00242b08: lhu a0,0x14(s0) */ set(4,half(ea(16,(int32_t)UINT32_C(0x00000014))));
/* 00242b0c: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 00242b10: jal 0x002d1b88 */ set(31,UINT64_C(0x00242b18));/* delay 00242b14 */ set(4,sx((uint32_t)cpu(4)<<1));body_002d1b88();
/* 00242b18: ori a1,zero,0xffe0 */ set(5,cpu(0)|UINT32_C(0x0000ffe0));
/* 00242b1c: dsll32 a1,a1,0xe */ set(5,cpu(5)<<46);
/* 00242b20: move a0,v0 */ set(4,cpu(2));
/* 00242b24: jal 0x002d18b0 */ set(31,UINT64_C(0x00242b2c));/* delay 00242b28 */ nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002d18b0),UINT32_C(0x00242b24));
/* 00242b2c: move a0,v0 */ set(4,cpu(2));
/* 00242b30: jal 0x002d1c40 */ set(31,UINT64_C(0x00242b38));/* delay 00242b34 */ body_002d1c40();
/* 00242b38: move a1,v0 */ set(5,cpu(2));
/* 00242b3c: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 00242b40: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 00242b44: bne v0,zero,0x00242b58 */ {int taken=(cpu(2)!=cpu(0));/* delay 00242b48 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00242b58;}}
/* 00242b4c: slti v1,a1,0x3e8 */ set(3,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x000003e8));
/* 00242b50: li v0,0x3e7 */ set(2,sx(UINT32_C(0x000003e7)));
/* 00242b54: movz a1,v0,v1 */ if(cpu(3)==0){set(5,cpu(2));}
L_00242b58:;
/* 00242b58: move v0,a1 */ set(2,cpu(5));
/* 00242b5c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00242b60: jr ra */ {uint64_t target=cpu(31);/* delay 00242b64 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00243c28(void){
uint64_t incoming=cpu(31);
/* 00243c28: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00243c2c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00243c30: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00243c34: move s1,a0 */ set(17,cpu(4));
/* 00243c38: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00243c3c: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00243c40: jal 0x00242a88 */ set(31,UINT64_C(0x00243c48));/* delay 00243c44 */ set(18,cpu(0));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00242a88),UINT32_C(0x00243c40));
/* 00243c48: move s0,v0 */ set(16,cpu(2));
/* 00243c4c: move a0,s1 */ set(4,cpu(17));
/* 00243c50: jal 0x00243f40 */ set(31,UINT64_C(0x00243c58));/* delay 00243c54 */ set(5,sx(UINT32_C(0x00000122)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00243f40),UINT32_C(0x00243c50));
/* 00243c58: move a0,s1 */ set(4,cpu(17));
/* 00243c5c: sll v1,s0,0x2 */ set(3,sx((uint32_t)cpu(16)<<2));
/* 00243c60: li a2,0x64 */ set(6,sx(UINT32_C(0x00000064)));
/* 00243c64: addu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));
/* 00243c68: li a1,0x123 */ set(5,sx(UINT32_C(0x00000123)));
/* 00243c6c: beq v0,zero,0x00243c88 */ {int taken=(cpu(2)==cpu(0));/* delay 00243c70 */ set(3,sx((uint32_t)cpu(3)<<1));if(taken){goto L_00243c88;}}
/* 00243c74: divu v1,a2 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(6),0,0);
/* 00243c78: beql a2,zero,0x00243c80 */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 00243c7c */ nocturneBattleRewardPhaseNativeTrap(7u,UINT32_C(0x00243c7c));goto L_00243c80;}}
L_00243c80:;
/* 00243c80: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00243c84: move s2,v0 */ set(18,cpu(2));
L_00243c88:;
/* 00243c88: jal 0x00243f40 */ set(31,UINT64_C(0x00243c90));/* delay 00243c8c */ nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00243f40),UINT32_C(0x00243c88));
/* 00243c90: beq v0,zero,0x00243cb8 */ {int taken=(cpu(2)==cpu(0));/* delay 00243c94 */ set(3,sx(UINT32_C(0x00000064)));if(taken){goto L_00243cb8;}}
/* 00243c98: sll v0,s0,0x2 */ set(2,sx((uint32_t)cpu(16)<<2));
/* 00243c9c: beql v1,zero,0x00243ca4 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00243ca0 */ nocturneBattleRewardPhaseNativeTrap(7u,UINT32_C(0x00243ca0));goto L_00243ca4;}}
L_00243ca4:;
/* 00243ca4: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 00243ca8: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00243cac: divu v0,v1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(3),0,0);
/* 00243cb0: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00243cb4: addu s2,s2,v0 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
L_00243cb8:;
/* 00243cb8: move a0,s1 */ set(4,cpu(17));
/* 00243cbc: jal 0x00243f40 */ set(31,UINT64_C(0x00243cc4));/* delay 00243cc0 */ set(5,sx(UINT32_C(0x00000124)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00243f40),UINT32_C(0x00243cbc));
/* 00243cc4: sll v1,s0,0x4 */ set(3,sx((uint32_t)cpu(16)<<4));
/* 00243cc8: li a0,0x64 */ set(4,sx(UINT32_C(0x00000064)));
/* 00243ccc: beq v0,zero,0x00243cec */ {int taken=(cpu(2)==cpu(0));/* delay 00243cd0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(16)));if(taken){goto L_00243cec;}}
/* 00243cd4: sll v0,v1,0x1 */ set(2,sx((uint32_t)cpu(3)<<1));
/* 00243cd8: beql a0,zero,0x00243ce0 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 00243cdc */ nocturneBattleRewardPhaseNativeTrap(7u,UINT32_C(0x00243cdc));goto L_00243ce0;}}
L_00243ce0:;
/* 00243ce0: divu v0,a0 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(4),0,0);
/* 00243ce4: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00243ce8: addu s2,s2,v0 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
L_00243cec:;
/* 00243cec: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 00243cf0: addu s0,s0,s2 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(18)));
/* 00243cf4: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 00243cf8: bne v0,zero,0x00243d08 */ {int taken=(cpu(2)!=cpu(0));/* delay 00243cfc */ set(3,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x000003e8));if(taken){goto L_00243d08;}}
/* 00243d00: li v0,0x3e7 */ set(2,sx(UINT32_C(0x000003e7)));
/* 00243d04: movz s0,v0,v1 */ if(cpu(3)==0){set(16,cpu(2));}
L_00243d08:;
/* 00243d08: move v0,s0 */ set(2,cpu(16));
/* 00243d0c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00243d10: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00243d14: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00243d18: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00243d1c: jr ra */ {uint64_t target=cpu(31);/* delay 00243d20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00243d28(void){
uint64_t incoming=cpu(31);
/* 00243d28: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00243d2c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00243d30: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00243d34: move s1,a0 */ set(17,cpu(4));
/* 00243d38: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00243d3c: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00243d40: jal 0x00242ae8 */ set(31,UINT64_C(0x00243d48));/* delay 00243d44 */ set(18,cpu(0));body_00242ae8();
/* 00243d48: move s0,v0 */ set(16,cpu(2));
/* 00243d4c: move a0,s1 */ set(4,cpu(17));
/* 00243d50: jal 0x00243f40 */ set(31,UINT64_C(0x00243d58));/* delay 00243d54 */ set(5,sx(UINT32_C(0x00000125)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00243f40),UINT32_C(0x00243d50));
/* 00243d58: move a0,s1 */ set(4,cpu(17));
/* 00243d5c: sll v1,s0,0x2 */ set(3,sx((uint32_t)cpu(16)<<2));
/* 00243d60: li a2,0x64 */ set(6,sx(UINT32_C(0x00000064)));
/* 00243d64: addu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));
/* 00243d68: li a1,0x126 */ set(5,sx(UINT32_C(0x00000126)));
/* 00243d6c: beq v0,zero,0x00243d88 */ {int taken=(cpu(2)==cpu(0));/* delay 00243d70 */ set(3,sx((uint32_t)cpu(3)<<1));if(taken){goto L_00243d88;}}
/* 00243d74: divu v1,a2 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(6),0,0);
/* 00243d78: beql a2,zero,0x00243d80 */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 00243d7c */ nocturneBattleRewardPhaseNativeTrap(7u,UINT32_C(0x00243d7c));goto L_00243d80;}}
L_00243d80:;
/* 00243d80: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00243d84: move s2,v0 */ set(18,cpu(2));
L_00243d88:;
/* 00243d88: jal 0x00243f40 */ set(31,UINT64_C(0x00243d90));/* delay 00243d8c */ nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00243f40),UINT32_C(0x00243d88));
/* 00243d90: beq v0,zero,0x00243db8 */ {int taken=(cpu(2)==cpu(0));/* delay 00243d94 */ set(3,sx(UINT32_C(0x00000064)));if(taken){goto L_00243db8;}}
/* 00243d98: sll v0,s0,0x2 */ set(2,sx((uint32_t)cpu(16)<<2));
/* 00243d9c: beql v1,zero,0x00243da4 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00243da0 */ nocturneBattleRewardPhaseNativeTrap(7u,UINT32_C(0x00243da0));goto L_00243da4;}}
L_00243da4:;
/* 00243da4: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 00243da8: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00243dac: divu v0,v1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(3),0,0);
/* 00243db0: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00243db4: addu s2,s2,v0 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
L_00243db8:;
/* 00243db8: move a0,s1 */ set(4,cpu(17));
/* 00243dbc: jal 0x00243f40 */ set(31,UINT64_C(0x00243dc4));/* delay 00243dc0 */ set(5,sx(UINT32_C(0x00000127)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00243f40),UINT32_C(0x00243dbc));
/* 00243dc4: sll v1,s0,0x4 */ set(3,sx((uint32_t)cpu(16)<<4));
/* 00243dc8: li a0,0x64 */ set(4,sx(UINT32_C(0x00000064)));
/* 00243dcc: beq v0,zero,0x00243dec */ {int taken=(cpu(2)==cpu(0));/* delay 00243dd0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(16)));if(taken){goto L_00243dec;}}
/* 00243dd4: sll v0,v1,0x1 */ set(2,sx((uint32_t)cpu(3)<<1));
/* 00243dd8: beql a0,zero,0x00243de0 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 00243ddc */ nocturneBattleRewardPhaseNativeTrap(7u,UINT32_C(0x00243ddc));goto L_00243de0;}}
L_00243de0:;
/* 00243de0: divu v0,a0 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(4),0,0);
/* 00243de4: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00243de8: addu s2,s2,v0 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
L_00243dec:;
/* 00243dec: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 00243df0: addu s0,s0,s2 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(18)));
/* 00243df4: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 00243df8: bne v0,zero,0x00243e08 */ {int taken=(cpu(2)!=cpu(0));/* delay 00243dfc */ set(3,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x000003e8));if(taken){goto L_00243e08;}}
/* 00243e00: li v0,0x3e7 */ set(2,sx(UINT32_C(0x000003e7)));
/* 00243e04: movz s0,v0,v1 */ if(cpu(3)==0){set(16,cpu(2));}
L_00243e08:;
/* 00243e08: move v0,s0 */ set(2,cpu(16));
/* 00243e0c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00243e10: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00243e14: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00243e18: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00243e1c: jr ra */ {uint64_t target=cpu(31);/* delay 00243e20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00244238(void){
uint64_t incoming=cpu(31);
/* 00244238: lw a2,-0x5750(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0024423c: lui a1,0x98 */ set(5,sx(UINT32_C(0x00980000)));
/* 00244240: ori a1,a1,0x967f */ set(5,cpu(5)|UINT32_C(0x0000967f));
/* 00244244: lw v0,0xa48(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000a48)));
/* 00244248: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 0024424c: slti v1,v0,0x0 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 00244250: movn v0,zero,v1 */ if(cpu(3)!=0){set(2,cpu(0));}
/* 00244254: slt a0,a1,v0 */ set(4,(int64_t)cpu(5)<(int64_t)cpu(2));
/* 00244258: movn v0,a1,a0 */ if(cpu(4)!=0){set(2,cpu(5));}
/* 0024425c: jr ra */ {uint64_t target=cpu(31);/* delay 00244260 */ sw(ea(6,(int32_t)UINT32_C(0x00000a48)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_002442e0(void){
uint64_t incoming=cpu(31);
/* 002442e0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002442e4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002442e8: move s0,a0 */ set(16,cpu(4));
/* 002442ec: andi a0,s0,0xffff */ set(4,cpu(16)&UINT32_C(0x0000ffff));
/* 002442f0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002442f4: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002442f8: jal 0x002138c0 */ set(31,UINT64_C(0x00244300));/* delay 002442fc */ set(17,cpu(5));body_002138c0();
/* 00244300: beq v0,zero,0x00244320 */ {int taken=(cpu(2)==cpu(0));/* delay 00244304 */ set(4,cpu(2));if(taken){goto L_00244320;}}
/* 00244308: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024430c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00244310: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00244314: j 0x002452c8 */ /* delay 00244318 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_002452c8();return;
L_00244320:;
/* 00244320: slti v0,s0,0x70 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000070));
/* 00244324: bne v0,zero,0x00244398 */ {int taken=(cpu(2)!=cpu(0));/* delay 00244328 */ lw(6,ea(28,(int32_t)UINT32_C(0xffffa8b0)));if(taken){goto L_00244398;}}
/* 0024432c: jal 0x001e0ed0 */ set(31,UINT64_C(0x00244334));/* delay 00244330 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000360)));body_001e0ed0();
/* 00244334: li v0,0x8d */ set(2,sx(UINT32_C(0x0000008d)));
/* 00244338: bnel s0,v0,0x002443e8 */ {int taken=(cpu(16)!=cpu(2));if(taken){/* delay 0024433c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002443e8;}}
/* 00244340: lw a0,-0x5750(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 00244344: blez s1,0x00244368 */ {int taken=((int64_t)cpu(17)<=0);/* delay 00244348 */ set(5,byte(ea(4,(int32_t)UINT32_C(0x000019b5))));if(taken){goto L_00244368;}}
/* 0024434c: addu a1,a1,s1 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(17)));
/* 00244350: slti v0,a1,0x64 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000064));
/* 00244354: beql v0,zero,0x0024438c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00244358 */ set(5,sx(UINT32_C(0x00000063)));goto L_0024438c;}}
/* 0024435c: b 0x00244390 */ /* delay 00244360 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(4)));goto L_00244390;
L_00244368:;
/* 00244368: bgez s1,0x00244390 */ {int taken=((int64_t)cpu(17)>=0);/* delay 0024436c */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(4)));if(taken){goto L_00244390;}}
/* 00244370: addu a1,a1,s1 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(17)));
/* 00244374: bgtzl a1,0x002443e4 */ {int taken=((int64_t)cpu(5)>0);if(taken){/* delay 00244378 */ sb(ea(2,(int32_t)UINT32_C(0x00001928)),(uint8_t)cpu(5));goto L_002443e4;}}
/* 0024437c: jal 0x001e0f10 */ set(31,UINT64_C(0x00244384));/* delay 00244380 */ set(4,sx(UINT32_C(0x000003ed)));body_001e0f10();
/* 00244384: lw a0,-0x5750(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 00244388: move a1,zero */ set(5,cpu(0));
L_0024438c:;
/* 0024438c: addu v0,s0,a0 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(4)));
L_00244390:;
/* 00244390: b 0x002443e4 */ /* delay 00244394 */ sb(ea(2,(int32_t)UINT32_C(0x00001928)),(uint8_t)cpu(5));goto L_002443e4;
L_00244398:;
/* 00244398: addiu a0,s0,0x1920 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00001920)));
/* 0024439c: slti v0,s0,0x60 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000060));
/* 002443a0: addu v1,a2,a0 */ set(3,sx((uint32_t)cpu(6)+(uint32_t)cpu(4)));
/* 002443a4: lbu a1,0x8(v1) */ set(5,byte(ea(3,(int32_t)UINT32_C(0x00000008))));
/* 002443a8: addu a1,a1,s1 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(17)));
/* 002443ac: slti v1,a1,0x0 */ set(3,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 002443b0: bne v0,zero,0x002443d0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002443b4 */ if(cpu(3)!=0){set(5,cpu(0));}if(taken){goto L_002443d0;}}
/* 002443b8: slti v0,a1,0x64 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000064));
/* 002443bc: beql v0,zero,0x002443dc */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002443c0 */ set(5,sx(UINT32_C(0x00000063)));goto L_002443dc;}}
/* 002443c4: b 0x002443e0 */ /* delay 002443c8 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(4)));goto L_002443e0;
L_002443d0:;
/* 002443d0: slti v1,a1,0x64 */ set(3,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000064));
/* 002443d4: li v0,0x63 */ set(2,sx(UINT32_C(0x00000063)));
/* 002443d8: movz a1,v0,v1 */ if(cpu(3)==0){set(5,cpu(2));}
L_002443dc:;
/* 002443dc: addu v0,a2,a0 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(4)));
L_002443e0:;
/* 002443e0: sb a1,0x8(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000008)),(uint8_t)cpu(5));
L_002443e4:;
/* 002443e4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002443e8:;
/* 002443e8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002443ec: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002443f0: jr ra */ {uint64_t target=cpu(31);/* delay 002443f4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002452b8(void){
uint64_t incoming=cpu(31);
/* 002452b8: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002452bc: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 002452c0: jr ra */ {uint64_t target=cpu(31);/* delay 002452c4 */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_002452c8(void){
uint64_t incoming=cpu(31);
/* 002452c8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002452cc: lw a1,-0x5750(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 002452d0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002452d4: move s0,a0 */ set(16,cpu(4));
/* 002452d8: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002452dc: lbu v0,0x1d7b(a1) */ set(2,byte(ea(5,(int32_t)UINT32_C(0x00001d7b))));
/* 002452e0: beq v0,zero,0x00245320 */ {int taken=(cpu(2)==cpu(0));/* delay 002452e4 */ set(6,cpu(0));if(taken){goto L_00245320;}}
/* 002452e8: move a3,v0 */ set(7,cpu(2));
/* 002452ec: addiu a0,a1,0x1cfb */ set(4,sx((uint32_t)cpu(5)+UINT32_C(0x00001cfb)));
/* 002452f0: lbu v1,0x0(a0) */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 002452f4: nop  */ 
L_002452f8:;
/* 002452f8: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 002452fc: beq v1,s0,0x0024536c */ {int taken=(cpu(3)==cpu(16));/* delay 00245300 */ set(2,cpu(0));if(taken){goto L_0024536c;}}
/* 00245304: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 00245308: slt v0,a2,a3 */ set(2,(int64_t)cpu(6)<(int64_t)cpu(7));
/* 0024530c: nop  */ 
/* 00245310: nop  */ 
/* 00245314: bnel v0,zero,0x002452f8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00245318 */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_002452f8;}}
/* 0024531c: lbu v0,0x1d7b(a1) */ set(2,byte(ea(5,(int32_t)UINT32_C(0x00001d7b))));
L_00245320:;
/* 00245320: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 00245324: sb s0,0x1cfb(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00001cfb)),(uint8_t)cpu(16));
/* 00245328: lw a0,-0x5750(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0024532c: lbu v0,0x1d7b(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00001d7b))));
/* 00245330: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 00245334: sb v0,0x1d7b(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00001d7b)),(uint8_t)cpu(2));
/* 00245338: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0024533c: addu v1,s0,v1 */ set(3,sx((uint32_t)cpu(16)+(uint32_t)cpu(3)));
/* 00245340: jal 0x00232880 */ set(31,UINT64_C(0x00245348));/* delay 00245344 */ sb(ea(3,(int32_t)UINT32_C(0x00001d3b)),(uint8_t)cpu(0));body_00232880();
/* 00245348: beq v0,zero,0x0024535c */ {int taken=(cpu(2)==cpu(0));/* delay 0024534c */ lw(5,ea(28,(int32_t)UINT32_C(0xffffa8b0)));if(taken){goto L_0024535c;}}
/* 00245350: jal 0x001e0ed0 */ set(31,UINT64_C(0x00245358));/* delay 00245354 */ set(4,sx(UINT32_C(0x00000860)));body_001e0ed0();
/* 00245358: lw a1,-0x5750(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
L_0024535c:;
/* 0024535c: andi a0,s0,0xff */ set(4,cpu(16)&UINT32_C(0x000000ff));
/* 00245360: jal 0x00222550 */ set(31,UINT64_C(0x00245368));/* delay 00245364 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000a54)));body_00222550();
/* 00245368: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_0024536c:;
/* 0024536c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00245370: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00245374: jr ra */ {uint64_t target=cpu(31);/* delay 00245378 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00269318(void){
uint64_t incoming=cpu(31);
/* 00269318: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0026931c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00269320: move s0,a0 */ set(16,cpu(4));
/* 00269324: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00269328: lw a0,0x34(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000034)));
/* 0026932c: blezl a0,0x0026943c */ {int taken=((int64_t)cpu(4)<=0);if(taken){/* delay 00269330 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0026943c;}}
/* 00269334: jal 0x00246038 */ set(31,UINT64_C(0x0026933c));/* delay 00269338 */ nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00246038),UINT32_C(0x00269334));
/* 0026933c: bnel v0,zero,0x0026943c */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00269340 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0026943c;}}
/* 00269344: lw v1,0x34(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000034)));
/* 00269348: sll v0,v1,0x2 */ set(2,sx((uint32_t)cpu(3)<<2));
/* 0026934c: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00269350: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00269354: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 00269358: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 0026935c: lui at,0x3b */ set(1,sx(UINT32_C(0x003b0000)));
/* 00269360: addiu at,at,-0x1020 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0xffffefe0)));
/* 00269364: addu v0,at,v0 */ set(2,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
/* 00269368: lbu t1,0x2(v0) */ set(9,byte(ea(2,(int32_t)UINT32_C(0x00000002))));
/* 0026936c: beq t1,zero,0x00269438 */ {int taken=(cpu(9)==cpu(0));/* delay 00269370 */ set(10,byte(ea(2,(int32_t)UINT32_C(0x00000003))));if(taken){goto L_00269438;}}
/* 00269374: beq t2,zero,0x00269438 */ {int taken=(cpu(10)==cpu(0));/* delay 00269378 */ set(7,sx((uint32_t)cpu(16)+UINT32_C(0x00000008)));if(taken){goto L_00269438;}}
/* 0026937c: move a1,zero */ set(5,cpu(0));
/* 00269380: move t0,a3 */ set(8,cpu(7));
/* 00269384: addiu t3,s0,0xc */ set(11,sx((uint32_t)cpu(16)+UINT32_C(0x0000000c)));
/* 00269388: addiu a2,a1,0x90 */ set(6,sx((uint32_t)cpu(5)+UINT32_C(0x00000090)));
/* 0026938c: nop  */ 
L_00269390:;
/* 00269390: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 00269394: addu v1,t0,a2 */ set(3,sx((uint32_t)cpu(8)+(uint32_t)cpu(6)));
/* 00269398: lbu v0,0x0(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 0026939c: bne v0,t1,0x002693b8 */ {int taken=(cpu(2)!=cpu(9));/* delay 002693a0 */ set(4,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000004));if(taken){goto L_002693b8;}}
/* 002693a4: addu v1,t3,a2 */ set(3,sx((uint32_t)cpu(11)+(uint32_t)cpu(6)));
/* 002693a8: lbu v0,0x0(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 002693ac: addu v0,v0,t2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(10)));
/* 002693b0: b 0x00269438 */ /* delay 002693b4 */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_00269438;
L_002693b8:;
/* 002693b8: bne a0,zero,0x00269390 */ {int taken=(cpu(4)!=cpu(0));/* delay 002693bc */ set(6,sx((uint32_t)cpu(5)+UINT32_C(0x00000090)));if(taken){goto L_00269390;}}
/* 002693c0: move a1,zero */ set(5,cpu(0));
/* 002693c4: move t0,a3 */ set(8,cpu(7));
/* 002693c8: addiu t3,s0,0xc */ set(11,sx((uint32_t)cpu(16)+UINT32_C(0x0000000c)));
/* 002693cc: addiu a2,a1,0x90 */ set(6,sx((uint32_t)cpu(5)+UINT32_C(0x00000090)));
L_002693d0:;
/* 002693d0: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 002693d4: addu a0,t0,a2 */ set(4,sx((uint32_t)cpu(8)+(uint32_t)cpu(6)));
/* 002693d8: lbu v0,0x0(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 002693dc: bne v0,zero,0x002693f8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002693e0 */ set(3,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000004));if(taken){goto L_002693f8;}}
/* 002693e4: addu v0,t3,a2 */ set(2,sx((uint32_t)cpu(11)+(uint32_t)cpu(6)));
/* 002693e8: sb t1,0x0(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(9));
/* 002693ec: b 0x00269438 */ /* delay 002693f0 */ sb(ea(2,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(10));goto L_00269438;
L_002693f8:;
/* 002693f8: bne v1,zero,0x002693d0 */ {int taken=(cpu(3)!=cpu(0));/* delay 002693fc */ set(6,sx((uint32_t)cpu(5)+UINT32_C(0x00000090)));if(taken){goto L_002693d0;}}
/* 00269400: addiu a0,a3,0x93 */ set(4,sx((uint32_t)cpu(7)+UINT32_C(0x00000093)));
/* 00269404: li a1,0x3 */ set(5,sx(UINT32_C(0x00000003)));
/* 00269408: addiu v1,s0,0x9f */ set(3,sx((uint32_t)cpu(16)+UINT32_C(0x0000009f)));
/* 0026940c: nop  */ 
L_00269410:;
/* 00269410: lbu v0,-0x1(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0xffffffff))));
/* 00269414: addiu a1,a1,-0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));
/* 00269418: sb v0,0x0(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 0026941c: addiu a0,a0,-0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffffff)));
/* 00269420: lbu v0,-0x1(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0xffffffff))));
/* 00269424: sb v0,0x0(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 00269428: bgtz a1,0x00269410 */ {int taken=((int64_t)cpu(5)>0);/* delay 0026942c */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));if(taken){goto L_00269410;}}
/* 00269430: sb t2,0x9c(s0) */ sb(ea(16,(int32_t)UINT32_C(0x0000009c)),(uint8_t)cpu(10));
/* 00269434: sb t1,0x98(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000098)),(uint8_t)cpu(9));
L_00269438:;
/* 00269438: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_0026943c:;
/* 0026943c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00269440: jr ra */ {uint64_t target=cpu(31);/* delay 00269444 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_0026a840(void){
uint64_t incoming=cpu(31);
/* 0026a840: lw v1,0x34(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000034)));
/* 0026a844: li v0,0x10b */ set(2,sx(UINT32_C(0x0000010b)));
/* 0026a848: beq v1,v0,0x0026a85c */ {int taken=(cpu(3)==cpu(2));/* delay 0026a84c */ lw(4,ea(4,(int32_t)UINT32_C(0x000000a4)));if(taken){goto L_0026a85c;}}
/* 0026a850: li v0,0x11c */ set(2,sx(UINT32_C(0x0000011c)));
/* 0026a854: bne v1,v0,0x0026a868 */ {int taken=(cpu(3)!=cpu(2));/* delay 0026a858 */ if(taken){goto L_0026a868;}}
L_0026a85c:;
/* 0026a85c: slti v1,a0,0x4e21 */ set(3,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00004e21));
/* 0026a860: li v0,0x4e20 */ set(2,sx(UINT32_C(0x00004e20)));
/* 0026a864: movz a0,v0,v1 */ if(cpu(3)==0){set(4,cpu(2));}
L_0026a868:;
/* 0026a868: jr ra */ {uint64_t target=cpu(31);/* delay 0026a86c */ set(2,cpu(4));checkReturn(target,incoming);return;}
}
static void body_0026a870(void){
uint64_t incoming=cpu(31);
/* 0026a870: lw v1,0x34(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000034)));
/* 0026a874: li v0,0x10b */ set(2,sx(UINT32_C(0x0000010b)));
/* 0026a878: beq v1,v0,0x0026a88c */ {int taken=(cpu(3)==cpu(2));/* delay 0026a87c */ lw(4,ea(4,(int32_t)UINT32_C(0x000000a0)));if(taken){goto L_0026a88c;}}
/* 0026a880: li v0,0x11c */ set(2,sx(UINT32_C(0x0000011c)));
/* 0026a884: bne v1,v0,0x0026a898 */ {int taken=(cpu(3)!=cpu(2));/* delay 0026a888 */ if(taken){goto L_0026a898;}}
L_0026a88c:;
/* 0026a88c: slti v1,a0,0x2711 */ set(3,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00002711));
/* 0026a890: li v0,0x2710 */ set(2,sx(UINT32_C(0x00002710)));
/* 0026a894: movz a0,v0,v1 */ if(cpu(3)==0){set(4,cpu(2));}
L_0026a898:;
/* 0026a898: jr ra */ {uint64_t target=cpu(31);/* delay 0026a89c */ set(2,cpu(4));checkReturn(target,incoming);return;}
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
uint32_t nocturneBattleRewardPhaseDependencyBody(uint32_t entry){switch(entry){
case UINT32_C(0x001005e8):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001005e8();return 1u;case UINT32_C(0x00100760):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00100760();return 1u;case UINT32_C(0x001009a0):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001009a0();return 1u;case UINT32_C(0x00100d70):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00100d70();return 1u;case UINT32_C(0x00100e08):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00100e08();return 1u;case UINT32_C(0x001015b0):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001015b0();return 1u;case UINT32_C(0x00101738):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00101738();return 1u;case UINT32_C(0x00101af8):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00101af8();return 1u;case UINT32_C(0x00101b80):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00101b80();return 1u;case UINT32_C(0x001e0ed0):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001e0ed0();return 1u;case UINT32_C(0x001e0f10):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001e0f10();return 1u;case UINT32_C(0x001fef20):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001fef20();return 1u;case UINT32_C(0x002138c0):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002138c0();return 1u;case UINT32_C(0x0021f838):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0021f838();return 1u;case UINT32_C(0x0021f898):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0021f898();return 1u;case UINT32_C(0x002221d0):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002221d0();return 1u;case UINT32_C(0x002224d8):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002224d8();return 1u;case UINT32_C(0x00222550):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00222550();return 1u;case UINT32_C(0x00223628):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00223628();return 1u;case UINT32_C(0x00223668):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00223668();return 1u;case UINT32_C(0x00223728):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00223728();return 1u;case UINT32_C(0x00223928):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00223928();return 1u;case UINT32_C(0x00232880):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00232880();return 1u;case UINT32_C(0x002328c8):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002328c8();return 1u;case UINT32_C(0x00242ae8):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00242ae8();return 1u;case UINT32_C(0x00243c28):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00243c28();return 1u;case UINT32_C(0x00243d28):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00243d28();return 1u;case UINT32_C(0x00244238):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00244238();return 1u;case UINT32_C(0x002442e0):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002442e0();return 1u;case UINT32_C(0x002452b8):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002452b8();return 1u;case UINT32_C(0x002452c8):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002452c8();return 1u;case UINT32_C(0x00269318):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00269318();return 1u;case UINT32_C(0x0026a840):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0026a840();return 1u;case UINT32_C(0x0026a870):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0026a870();return 1u;case UINT32_C(0x002d1b88):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002d1b88();return 1u;case UINT32_C(0x002d1c40):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002d1c40();return 1u;case UINT32_C(0x002d34a0):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002d34a0();return 1u;case UINT32_C(0x002d3578):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002d3578();return 1u;
default:return 0u;}}
uint64_t ps2BattleRewardPhaseDependency_0021F838(void){body_0021f838();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_0021F898(void){body_0021f898();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_00223628(void){body_00223628();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_00223668(void){body_00223668();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_00223728(void){body_00223728();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_00223928(void){body_00223928();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_001FEF20(void){body_001fef20();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_00243C28(void){body_00243c28();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_00243D28(void){body_00243d28();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_00244238(void){body_00244238();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_002442E0(void){body_002442e0();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_002138C0(void){body_002138c0();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_001E0ED0(void){body_001e0ed0();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_001E0F10(void){body_001e0f10();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_001005E8(void){body_001005e8();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_00100760(void){body_00100760();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_001009A0(void){body_001009a0();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_00100D70(void){body_00100d70();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_00100E08(void){body_00100e08();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_001015B0(void){body_001015b0();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_00101738(void){body_00101738();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_00101AF8(void){body_00101af8();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_00101B80(void){body_00101b80();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_002452B8(void){body_002452b8();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_00269318(void){body_00269318();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_0026A840(void){body_0026a840();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_0026A870(void){body_0026a870();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_00242AE8(void){body_00242ae8();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_002D1B88(void){body_002d1b88();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_002D1C40(void){body_002d1c40();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_002D34A0(void){body_002d34a0();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_002D3578(void){body_002d3578();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_002452C8(void){body_002452c8();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_00222550(void){body_00222550();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_00232880(void){body_00232880();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_002328C8(void){body_002328c8();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_002224D8(void){body_002224d8();return cpu(2);}
uint64_t ps2BattleRewardPhaseDependency_002221D0(void){body_002221d0();return cpu(2);}
