/* Whole six original worker/process bootstrap bodies; four registered, two pending.
 * Fixed statements/labels retain original operation and delay positions.
 * No opcode loop, game-result callback, captured output, stack patch or
 * caller-filled local target list. Native frames occupy actual shared RAM.
 */
#include "battle_action_skill_worker_bootstrap_frames.h"
#include "battle_action_consumer.h"
#include "battle_action_formula_frames.h"
#include "effect_host_bindings.h"
#include "pcp_effect_helpers.h"
#include "magatuhi_helpers.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include "compiler_numeric.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#ifdef _MSC_VER
#pragma warning(disable:4102)
#endif
extern uint64_t nocturneEffectHostLo(void);
extern uint64_t nocturneEffectHostHi(void);
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleActionConsumerAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sb(uint32_t a,uint8_t v){*at(a)=v;}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];if(!r)return 0;nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];if(!r)return;nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}


static void checkReturn(uint64_t target,uint64_t incoming){if((uint32_t)target!=(uint32_t)incoming)abort();}
/* Genuine EE word division is defined even before a late native BREAK.
 * Primary and secondary banks are distinct; use the existing Formula bank
 * for cross-unit secondary state rather than a private or primary substitute.
 */



static void body_001005e8(void);
static void body_00100760(void);
static void body_001009a0(void);
static void body_001015b0(void);
static void body_00297870(void);
static void body_00297890(void);
static void body_001005e8(void){
nocturneEffectAxisNoteEntry(0x001005e8u);
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
nocturneEffectAxisNoteEntry(0x00100760u);
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
nocturneEffectAxisNoteEntry(0x001009a0u);
uint64_t incoming=cpu(31);
/* 001009a0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001009a4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001009a8: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001009ac: jal 0x001005e8 */ set(31,0x001009b4u);/* delay 001009b0 */ set(16,cpu(4));body_001005e8();
/* 001009b4: lw v0,0x1c(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 001009b8: li v1,-0x10 */ set(3,sx(UINT32_C(0xfffffff0)));
/* 001009bc: move a0,s0 */ set(4,cpu(16));
/* 001009c0: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 001009c4: ori v0,v0,0x2 */ set(2,cpu(2)|UINT32_C(0x00000002));
/* 001009c8: jal 0x00100760 */ set(31,0x001009d0u);/* delay 001009cc */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));body_00100760();
/* 001009d0: sw zero,0x24(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(0));
/* 001009d4: sw zero,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(0));
/* 001009d8: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001009dc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001009e0: jr ra */ {uint64_t target=cpu(31);/* delay 001009e4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_001015b0(void){
nocturneEffectAxisNoteEntry(0x001015b0u);
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
/* 001015f4: jal 0x002a8af8 */ set(31,0x001015fcu);/* delay 001015f8 */ set(23,cpu(10));nocturneBattleActionSkillCall(0x002a8af8u);
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
/* 001016a0: jal 0x00100760 */ set(31,0x001016a8u);/* delay 001016a4 */ sw(ea(16,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(0));body_00100760();
/* 001016a8: lh v0,0x2c(s0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x0000002c))));
/* 001016ac: bne v0,zero,0x001016c0 */ {int taken=(cpu(2)!=cpu(0));/* delay 001016b0 */ set(2,cpu(16));if(taken){goto L_001016c0;}}
/* 001016b4: jal 0x001009a0 */ set(31,0x001016bcu);/* delay 001016b8 */ set(4,cpu(16));body_001009a0();
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
static void body_00297870(void){
nocturneEffectAxisNoteEntry(0x00297870u);
uint64_t incoming=cpu(31);
/* 00297870: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00297874: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00297878: jal 0x002976c0 */ set(31,0x00297880u);/* delay 0029787c */ nocturneBattleActionSkillCall(0x002976c0u);
/* 00297880: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00297884: move v0,zero */ set(2,cpu(0));
/* 00297888: jr ra */ {uint64_t target=cpu(31);/* delay 0029788c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00297890(void){
nocturneEffectAxisNoteEntry(0x00297890u);
uint64_t incoming=cpu(31);
/* 00297890: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00297894: move a1,zero */ set(5,cpu(0));
/* 00297898: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0029789c: lui s0,0x57 */ set(16,sx(UINT32_C(0x00570000)));
/* 002978a0: addiu s0,s0,0x5618 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00005618)));
/* 002978a4: li a2,0x40 */ set(6,sx(UINT32_C(0x00000040)));
/* 002978a8: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002978ac: jal 0x002d4558 */ set(31,0x002978b4u);/* delay 002978b0 */ set(4,cpu(16));nocturneBattleActionSkillCall(0x002d4558u);
/* 002978b4: li v1,0x4 */ set(3,sx(UINT32_C(0x00000004)));
/* 002978b8: sb v1,0x7(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000007)),(uint8_t)cpu(3));
/* 002978bc: li a1,0x7f */ set(5,sx(UINT32_C(0x0000007f)));
/* 002978c0: move a2,zero */ set(6,cpu(0));
/* 002978c4: jal 0x002a8080 */ set(31,0x002978ccu);/* delay 002978c8 */ set(4,sx(UINT32_C(0x00000001)));nocturneBattleActionSkillCall(0x002a8080u);
/* 002978cc: lui a0,0x4 */ set(4,sx(UINT32_C(0x00040000)));
/* 002978d0: jal 0x002a9038 */ set(31,0x002978d8u);/* delay 002978d4 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));nocturneBattleActionSkillCall(0x002a9038u);
/* 002978d8: jal 0x002a9688 */ set(31,0x002978e0u);/* delay 002978dc */ set(4,cpu(2));nocturneBattleActionSkillCall(0x002a9688u);
/* 002978e0: lui a0,0x55 */ set(4,sx(UINT32_C(0x00550000)));
/* 002978e4: sw v0,0x1c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));
/* 002978e8: lui t0,0x29 */ set(8,sx(UINT32_C(0x00290000)));
/* 002978ec: addiu a0,a0,0x1650 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00001650)));
/* 002978f0: addiu t0,t0,0x7870 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00007870)));
/* 002978f4: li a1,0x384 */ set(5,sx(UINT32_C(0x00000384)));
/* 002978f8: li a2,0x1 */ set(6,sx(UINT32_C(0x00000001)));
/* 002978fc: move a3,zero */ set(7,cpu(0));
/* 00297900: move t1,zero */ set(9,cpu(0));
/* 00297904: jal 0x001015b0 */ set(31,0x0029790cu);/* delay 00297908 */ set(10,cpu(0));body_001015b0();
/* 0029790c: lui v1,0x29 */ set(3,sx(UINT32_C(0x00290000)));
/* 00297910: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00297914: addiu v1,v1,0x76c0 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x000076c0)));
/* 00297918: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0029791c: sw v1,-0x2798(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd868)),(uint32_t)cpu(3));
/* 00297920: jr ra */ {uint64_t target=cpu(31);/* delay 00297924 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint32_t nocturneBattleActionSkillWorkerBootstrapBody(uint32_t entry){switch(entry){
case 0x001005e8u:body_001005e8();return 1u;
case 0x00100760u:body_00100760();return 1u;
case 0x001009a0u:body_001009a0();return 1u;
case 0x001015b0u:body_001015b0();return 1u;
case 0x00297870u:body_00297870();return 1u;
case 0x00297890u:body_00297890();return 1u;
default:return 0u;}}
